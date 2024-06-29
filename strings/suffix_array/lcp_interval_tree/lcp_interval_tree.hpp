/**
 * @code{.cpp}
       vector<ll> a;
       vi le = mono_st(a, less()); // greater(), less_equal(), greater_equal()
 * @endcode
 * @param a array
 * @param cmp transitive compare operator
 * @returns vector le where le[i] = max index such that: le[i] < i and
 *          cmp(a[le[i]], a[i]). If no index exists, le[i] = -1
 * @time O(n)
 * @space a O(n) vector is allocated and returned
 */
template <class T, class F> vector<int> mono_st(const vector<T>& a, F cmp) {
  vector<int> le((int)size(a));
  for (int i = 0; i < ((int)size(a)); i++)
    for (le[i] = i - 1; le[i] >= 0 && !cmp(a[le[i]], a[i]);) le[i] = le[le[i]];
  return le;
}
/**
 * @code{.cpp}
       vector<ll> a;
       auto le = mono_st(a, less()), ri = mono_range(le); // greater(), less_equal(), greater_equal()
 * @endcode
 * @param le monotonic stack array of a
 * @returns vector ri where ri[i] = min index such that: i < ri[i] and
 *          !cmp(a[i], a[ri[i]]). If no index exists, ri[i] = n
 * @time O(n)
 * @space a O(n) vector is allocated and returned
 */
vector<int> mono_range(const vector<int>& le) {
  vector<int> ri((int)size(le), (int)size(le));
  for (int i = 0; i < ((int)size(le)); i++)
    for (int j = i - 1; j != le[i]; j = le[j]) ri[j] = i;
  return ri;
}
/**
 *   when cmp is less():
 *   a = {2, 1, 3, 1, 1, 0, 1, 2, 2, 0, 2}
 *       (---------------------------x---)
 *       (------------x)   (x------) | (x)
 *       (x)   (x)    |     | (---x) |  |
 *        |     |     |     |     |  |  |
 * index: 0  1  2  3  4  5  6  7  8  9  10
 *
 * nodes are the right-most min/max of their subarray:
 * p[0] = p[2] = 4
 * p[8] = 6
 * p[4] = p[6] = p[10] = 9
 * p[9] = -1 (root)
 *
 * indexes 1, 3, 5, 7 are not nodes; here p maps i to right-most min/max in their subarray:
 * p[1] = p[3] = 4
 * p[7] = 8
 * p[5] = 9
 *
 * @code{.cpp}
       auto le = mono_st(a, less()), p = cart_k_ary_tree(a, le); // min cart tree
       auto le = mono_st(a, greater()), p = cart_k_ary_tree(a, le); // max cart tree
       bool is_node = (p[i] < i || a[i] != a[p[i]]);
 * @endcode
 *
 * @param a,le array and its left-monotonic stack
 * @returns parent array
 * @time O(n)
 * @space a O(n) vector is allocated and returned
 */
template <class T> vector<int> cart_k_ary_tree(const vector<T>& a, const vector<int>& le) {
  vector<int> p(le);
  for (int i = (int)size(a) - 1; i >= 0; i--)
    for (int j = i - 1; j != le[i]; j = le[j])
      if (le[j] == le[i] || a[i] == a[le[j]])
        p[j] = (p[i] < i || a[i] != a[p[i]] ? i : p[i]);
  return p;
}
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
const int mn = '0', cnt_let = 36;  // mn <= s[i] < mn + cnt_let; for lowercase letters: mn = 'a', cnt_let = 26
/**
 * @see Replacing suffix trees with enhanced suffix arrays by Mohamed Ibrahim
 * Abouelhoda, Stefan Kurtz, Enno Ohlebusch
 *
 * offline version of suffix tree, idea: min k-ary cartesian tree of LCP array
 * corresponds exactly to the internal nodes of the suffix tree. Then add in <=
 * n nodes, one for each suffix, and it corresponds to the suffix tree.
 *
 * string = "cabcabacaabc"
 *                                              c
 *              c                               b
 *              b               c               a
 *              a               b           c   a
 *      c       a               a           b   c
 *      b       c       c       a           a   a
 *      a       a   c   b       c           a   b
 *      a       b   b   a       a       c   c   a
 *  c   c       a   a   a       b       b   a   c
 *  b   a   c | c   a   c       a       a   b | b
 *  a   b | b | b   c   a   c | c       a | a | a
 *  a | a | a | a | a   b | b | b   c | c | c | c
 *    1   2   3   1   0   1   2   0   1   2   3   <- LCP
 * (------------------------------R--------------)
 * (--------------a--) (--b------) (--c----------)
 * (a) (--b------) (c) (a) (--c--)     (--a------)
 *     (a) (--c--)             (a)     (a) (--b--)
 *             (a)                         (a) (c)
 *
 * note leaf nodes dont exist when that suffix is a prefix of a longer suffix
 *
 * @code{.cpp}
       string s;
       lcp_tree lt(s);
 * @endcode
 *
 * internal nodes are a subset of [0, n - 1), each internal node represents:
 *     - a prefix of some suffix; in the suffix tree, each edge has some substring. This prefix of suffix corresponds to this substring
 *     - a range in the suffix array
 *     - a lcp number of this range of suffixes representing length of prefix of these suffixes
 * leaf nodes are a subset of [n - 1, 2 * n - 1), each leaf represents:
 *     - a single suffix
 */
struct lcp_tree {
  suffix_array<string> sf_a;
  vector<int> le, ri;
  int root;
  vector<vector<int>> adj;
  /**
   * @param s non-empty string/array
   * @time O((n log n) + (mn + cnt_let) + (n * cnt_let))
   * @space adj is O(n * cnt_let)
   */
  lcp_tree(const string& s) : sf_a(s, mn + cnt_let), le(mono_st(sf_a.lcp, less())), ri(mono_range(le)), adj(max(sf_a.n - 1, 0), vector(cnt_let, -1)) {
    assert(sf_a.n > 0);
    vector<int> p = cart_k_ary_tree(sf_a.lcp, le);
    root = find(begin(p), end(p), -1) - begin(p);
    auto node = [&](int i) -> int {
      return p[i] < i || sf_a.lcp[i] != sf_a.lcp[p[i]] ? i : p[i];
    };
    for (int i = 0; i < ((int)size(p)); i++)
      if (node(i) == i && i != root) adj[p[i]][s[sf_a.sa[i] + sf_a.lcp[p[i]]] - mn] = i;
    for (int i = 0; i < (sf_a.n); i++) {
      int prev_lcp = (i ? sf_a.lcp[i - 1] : 0);
      int next_lcp = (i < (int)size(sf_a.lcp) ? sf_a.lcp[i] : -1);
      int u = (prev_lcp > next_lcp) ? i - 1 : node(i);
      int idx = sf_a.sa[i] + max(prev_lcp, next_lcp);
      if (u == -1 || idx == sf_a.n) continue;
      adj[u][s[idx] - mn] = sf_a.n - 1 + i;
    }
  }
  /**
   * @param u node
   * @returns range [le, ri) such that the following (ri - le) substrings are equal:
   *     - for all i in [le, ri): s.substr(sa[i], lcp_len(u))
   * @time O(1)
   * @space O(1)
   */
  inline pair<int, int> sa_range(int u) {
    if (u < sf_a.n - 1) return {le[u] + 1, ri[u] + 1};
    return {u - sf_a.n + 1, u - sf_a.n + 2};
  }
  /**
   * @param u node
   * @returns length of longest common prefix of u's interval/range
   * @time O(1)
   * @space O(1)
   */
  inline int len_lcp_range(int u) {
    return u < sf_a.n - 1 ? sf_a.lcp[u] : sf_a.n - sf_a.sa[u - sf_a.n + 1];
  }
  /**
   * @param u node
   * @param c letter (don't subtract mn)
   * @returns child of u following edge with label c, -1 means child doesn't exist
   * @time O(1)
   * @space O(1)
   */
  inline int get_child(int u, char c) {
    return u < sf_a.n - 1 ? adj[u][c - mn] : -1;
  }
  /**
   * performs trie-style downwards tree walk
   * @param t needle
   * @returns range [le, ri) such that:
   *     - for all i in [le, ri): t == s.substr(sa[i], sz(t))
   *     - `ri - le` is the # of matches of t in s.
   * @time O(|t|)
   * @space O(1)
   */
  pair<int, int> find_str(const string& t) {
    int u = root;
    for (int i = 0; i < ((int)size(t)); i++) {
      if (i == len_lcp_range(u)) {
        u = get_child(u, t[i]);
        if (u == -1) return {0, 0};
      }
      int sa_le = sa_range(u).first;
      if (sf_a.s[sf_a.sa[sa_le] + i] != t[i]) return {0, 0};
    }
    return sa_range(u);
  }
};
