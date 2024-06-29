/**
 * @code{.cpp}
       vector<ll> a;
       RMQ rmq(a, ranges::min); // -std=c++20
       RMQ rmq(a, [&](auto& x, auto& y) { return min(x, y); });
 * @endcode
 */
template <class T, class F> struct RMQ {
  vector<vector<T>> dp;
  F op;
  RMQ() {}
  /**
   * @param a static array
   * @param a_op any associative, commutative, idempotent operation
   * @time O(n log n)
   * @space O(n log n) for `dp` vector
   */
  RMQ(const vector<T>& a, F a_op) : dp(1, a), op(a_op) {
    for (int i = 0; (2 << i) <= (int)size(a); i++) {
      dp.emplace_back((int)size(a) - (2 << i) + 1);
      transform(begin(dp[i]), end(dp[i]) - (1 << i), begin(dp[i]) + (1 << i), begin(dp[i + 1]), op);
    }
  }
  /**
   * @param le,ri defines range [le, ri)
   * @returns a[le] op a[le + 1] op ... op a[ri - 1]
   * @time O(1)
   * @space O(1)
   */
  inline T query(int le, int ri) {
    assert(0 <= le && le < ri && ri <= (int)size(dp[0]));
    int lg = __lg(ri - le);
    return op(dp[lg][le], dp[lg][ri - (1 << lg)]);
  }
};
/**
 * subarray of `sa` of matches, and example of longest matching prefix of t in s
 */
struct match {
  /**
   * t is some string defined by the query
   *
   * [sa_le, sa_ri) defines subarray of suffix array such that:
   * - for all i in [sa_le, sa_ri): t == s.substr(sa[i], sz(t))
   * - `sa_ri - sa_le` is the # of matches of t in s.
   *
   * [s_le, s_ri) defines a substring of s such that:
   * - s.substr(s_le, s_ri - s_le) == t.substr(0, s_ri - s_le)
   * - (s_ri - s_le) is maximized, if there are multiple answers, s_le is arbitrary
   *
   * - note if sa_le < sa_ri, i.e. at least one match, then s_ri - s_le == sz(t)
   * - note if sa_le == sa_ri, i.e. no matches, then s_ri - s_le < sz(t)
   * @{
   */
  int sa_le, sa_ri, s_le, s_ri;
  /** @} */
};
/**
 * @see https://github.com/kth-competitive-programming/kactl /blob/main/content/strings/SuffixArray.h
 */
template <class T> struct suffix_array {
  T s;
  int n;
  /**
   * suffixes of "banana":
   * 0 banana 3
   * 1 anana  2
   * 2 nana   5
   * 3 ana    1
   * 4 na     4
   * 5 a      0
   *
   * 5 a      0
   *   |
   * 3 ana    1
   *   |||
   * 1 anana  2
   *
   * 0 banana 3
   *
   * 4 na     4
   *   ||
   * 2 nana   5
   *
   * sa = {5, 3, 1, 0, 4, 2}
   * sa_inv = {3, 2, 5, 1, 4, 0} (sa[sa_inv[i]] == i, sa_inv[sa[i]] == i)
   * lcp = {1, 3, 0, 0, 2}
   * @{
   */
  vector<int> sa, sa_inv, lcp;
  /** @} */
  /**
   * @code{.cpp}
         string s;
         suffix_array sf_a(s, 256);
         auto [_, __, sa, sa_inv, lcp, ___] = suffix_array(s, 256);
         // or
         vi a;
         suffix_array sf_a(a, 100'005);
   * @endcode
   * @param a_s,max_num string/array with 0 <= a_s[i] < max_num
   * @time O((n log n) + max_num)
   * @space vectors `sa`, `sa_inv`, `lcp` are O(n); `rmq` is O(nlogn), vector
   * `freq` is O(max_num) and is allocated temporarily
   */
  suffix_array(const T& a_s, int max_num) : s(a_s), n((int)size(s)), sa(n), sa_inv(begin(s), end(s)), lcp(max(0, n - 1)) {
    vector<int> tmp(n);
    iota(begin(sa), end(sa), 0);
    for (int ln = 0; ln < n; ln = max(1, 2 * ln)) {
      iota(begin(tmp), begin(tmp) + ln, n - ln);
      copy_if(begin(sa), end(sa), begin(tmp) + ln, [&](int& num) { return (num -= ln) >= 0; });
      vector<int> freq(max_num);
      for (int num : sa_inv) freq[num]++;
      partial_sum(begin(freq), end(freq), begin(freq));
      for_each(rbegin(tmp), rend(tmp), [&](int t) { sa[--freq[sa_inv[t]]] = t; });
      swap(sa_inv, tmp);
      max_num = 1, sa_inv[sa[0]] = 0;
      auto prev_inv = [&](int i) { return pair(tmp[i], i + ln < n ? tmp[i + ln] : -1); };
      for (int i = 1; i < (n); i++) {
        max_num += prev_inv(sa[i - 1]) != prev_inv(sa[i]);
        sa_inv[sa[i]] = max_num - 1;
      }
      if (max_num == n) break;
    }
    int sz = 0;
    for (int i = 0; i < (n); i++) {
      if (sz > 0) sz--;
      if (sa_inv[i] == 0) continue;
      for (int j = sa[sa_inv[i] - 1]; max(i, j) + sz < n && s[i + sz] == s[j + sz];) sz++;
      lcp[sa_inv[i] - 1] = sz;
    }
  }
  RMQ<int, function<int(int, int)>> rmq;
  /**
   * @param i1,i2 defines substrings [i1, n), [i2, n)
   *      - passing i1,i2 = n is okay
   *      - if one of the suffixes is the entire string (i1 == 0 || i2 == 0) then
   *        it's the same as z algorithm
   * @returns max integer k such that s.substr(i1, k) == s.substr(i2, k)
   * @time O(1)
   * @space O(1)
   */
  inline int len_lcp(int i1, int i2) {
    if (i1 > i2) swap(i1, i2);
    assert(0 <= i1 && i2 <= n);
    if (i1 == i2 || i2 == n) return n - i2;
    if (empty(rmq.dp)) rmq = {lcp, [](int x, int y) { return min(x, y); }};
    auto [le, ri] = minmax(sa_inv[i1], sa_inv[i2]);
    return rmq.query(le, ri);
  }
  /**
   * @param le1,le2 defines suffixes [le1, n), [le2, n)
   *      - passing le1,le2 = n is okay
   * @returns a number `cmp` where:
   *     - cmp < 0 iff s.substr(le1) < s.substr(le2)
   *     - cmp = 0 iff s.substr(le1) = s.substr(le2)
   *     - cmp > 0 iff s.substr(le1) > s.substr(le2)
   * @time O(1)
   * @space O(1)
   */
  inline int cmp_sufs(int le1, int le2) {
    assert(0 <= min(le1, le2) && max(le1, le2) <= n);
    return max(le1, le2) == n ? le2 - le1 : sa_inv[le1] - sa_inv[le2];
  }
  /**
   * @param le1,ri1 first substring [le1, ri1)
   * @param le2,ri2 second substring [le2, ri2)
   * @returns a number `cmp` where:
   *     - cmp < 0 iff s.substr(le1, ri1 - le1) < s.substr(le2, ri2 - le2)
   *     - cmp = 0 iff s.substr(le1, ri1 - le1) = s.substr(le2, ri2 - le2)
   *     - cmp > 0 iff s.substr(le1, ri1 - le1) > s.substr(le2, ri2 - le2)
   * @time O(1)
   * @space O(1)
   */
  inline int cmp_substrs(int le1, int ri1, int le2, int ri2) {
    assert(0 <= le1 && le1 <= ri1 && ri1 <= n);
    assert(0 <= le2 && le2 <= ri2 && ri2 <= n);
    int len1 = ri1 - le1;
    int len2 = ri2 - le2;
    return len_lcp(le1, le2) >= min(len1, len2) ? len1 - len2 : sa_inv[le1] - sa_inv[le2];
  }
  /**
   * @see https://github.com/yosupo06/Algorithm/blob /master/src/string/suffixarray.hpp
   * @param t query string
   * @returns range [le, ri) such that:
   *     - for all i in [le, ri): t == s.substr(sa[i], sz(t))
   *     - `ri - le` is the # of matches of t in s.
   * @time O(|t| * log(|s|))
   * @space O(1)
   */
  inline pair<int, int> find_str(const T& t) {
    int le = lower_bound(begin(sa), end(sa), 0, [&](int i, int) -> bool { return lexicographical_compare(i + begin(s), end(s), begin(t), end(t)); }) - begin(sa);
    int ri = lower_bound(le + begin(sa), end(sa), 0, [&](int i, int) -> bool { return mismatch(begin(t), end(t), i + begin(s), end(s)).first == end(t); }) - begin(sa);
    return {le, ri};
  }
  /**
   * @param t query string
   * @returns see match
   * @time O(|t| * log(|s|))
   * @space O(1)
   */
  inline match find_str_long(const T& t) {
    int s_le = 0, s_ri = 0;
    auto cmp = [&](int i, int cmp_num) -> bool {
      auto [it_t, it_s] = mismatch(begin(t), end(t), i + begin(s), end(s));
      if (it_s - begin(s) - i > s_ri - s_le) s_le = i, s_ri = it_s - begin(s);
      if (it_s != end(s) && it_t != end(t)) return (*it_s) - (*it_t) < cmp_num;
      return cmp_num ^ ((int)size(s) - i < (int)size(t));
    };
    int sa_le = lower_bound(begin(sa), end(sa), 0, cmp) - begin(sa);
    int sa_ri = lower_bound(sa_le + begin(sa), end(sa), 1, cmp) - begin(sa);
    return {sa_le, sa_ri, s_le, s_ri};
  }
  /**
   * @param s_le,s_ri defines a substring [s_le, s_ri) of s
   * @returns a range [le, ri) such that:
   *     - for all i in [le, ri): s.substr(s_le, s_ri - s_le) == s.substr(sa[i], s_ri - s_le)
   *     - `ri - le` is the # of matches of s.substr(s_le, s_ri - s_le) in s.
   * @time O(log(|s|))
   * @space O(1)
   */
  inline pair<int, int> find_substr(int s_le, int s_ri) {
    assert(0 <= s_le && s_le <= s_ri && s_ri <= n);
    if (s_le == n) return {0, n};
    auto cmp = [&](int i, bool flip) -> bool {
      return flip ^ (len_lcp(i, s_le) < s_ri - s_le);
    };
    int le = lower_bound(begin(sa), begin(sa) + sa_inv[s_le], 0, cmp) - begin(sa);
    int ri = lower_bound(sa_inv[s_le] + 1 + begin(sa), end(sa), 1, cmp) - begin(sa);
    return {le, ri};
  }
  /**
   * @param substrs this defines query string t as:
   *     s.substr(substrs[0][0], substrs[0][1] - substrs[0][0]) +
   *     s.substr(substrs[1][0], substrs[1][1] - substrs[1][0]) +
   *     ...
   *     s.substr(substrs.back()[0], substrs.back()[1] - substrs.back()[0])
   * @returns see match
   * @time O(sz(substrs) * log(|s|))
   * @space O(1)
   */
  inline match find_substrs_concated(const vector<pair<int, int>>& substrs) {
    using dt = array<int, 3>;
    int sa_le = 0, sa_ri = n, s_le = 0, s_ri = 0, sum_len = 0;
    auto cmp = [&](int i, const dt& x) -> bool {
      int j = i + sum_len, lcp_len = min(len_lcp(j, x[0]), x[1]);
      if (lcp_len + sum_len > s_ri - s_le) s_le = i, s_ri = j + lcp_len;
      if (lcp_len < min(n - j, x[1])) return sa_inv[j] - sa_inv[x[0]] < x[2];
      return x[2] ^ (n - j < x[1]);
    };
    for (auto [le, ri] : substrs) {
      assert(0 <= le && le <= ri && ri <= n);
      sa_le = lower_bound(begin(sa) + sa_le, begin(sa) + sa_ri, dt{le, ri - le, 0}, cmp) - begin(sa);
      sa_ri = lower_bound(begin(sa) + sa_le, begin(sa) + sa_ri, dt{le, ri - le, 1}, cmp) - begin(sa);
      sum_len += ri - le;
    }
    return {sa_le, sa_ri, s_le, s_ri};
  }
};
