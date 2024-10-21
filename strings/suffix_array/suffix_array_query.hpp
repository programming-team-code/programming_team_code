//! https://github.com/kth-competitive-programming/kactl/blob/main/content/strings/SuffixArray.h
//!
//! 0 banana 3
//! 1 anana  2
//! 2 nana   5
//! 3 ana    1
//! 4 na     4
//! 5 a      0
//!
//! 5 a      0
//!   |
//! 3 ana    1
//!   |||
//! 1 anana  2
//!
//! 0 banana 3
//!
//! 4 na     4
//!   ||
//! 2 nana   5
//!
//! sa = {5, 3, 1, 0, 4, 2}
//! sa_inv = {3, 2, 5, 1, 4, 0}
//! lcp = {1, 3, 0, 0, 2}
//!
//! @code
//!   auto [sa, sa_inv, lcp] = get_sa(s, 256);
//! @endcode
//!
//! requires 0<=s[i]<max_num
//!
//! @time O(nlogn + max_num)
//! @space O(n + max_num)
template<class T>
array<vector<int>, 3> get_sa(const T& s, int max_num) {
  int n = ssize(s);
  vector<int> sa(n), sa_inv(begin(s), end(s)),
    lcp(max(0, n - 1));
  iota(begin(sa), end(sa), 0);
  for (int ln = 0; ln < n; ln = max(1, 2 * ln)) {
    vector<int> tmp(n), freq(max_num);
    iota(begin(tmp), begin(tmp) + ln, n - ln);
    copy_if(begin(sa), end(sa), begin(tmp) + ln,
      [&](int& x) { return (x -= ln) >= 0; });
    for (int x : sa_inv) freq[x]++;
    partial_sum(begin(freq), end(freq), begin(freq));
    for_each(rbegin(tmp), rend(tmp),
      [&](int x) { sa[--freq[sa_inv[x]]] = x; });
    swap(sa_inv, tmp);
    max_num = 1, sa_inv[sa[0]] = 0;
    auto prev_inv = [&](int i) {
      return pair(tmp[i], i + ln < n ? tmp[i + ln] : -1);
    };
    for (int i = 1; i < n; i++) {
      max_num += prev_inv(sa[i - 1]) != prev_inv(sa[i]);
      sa_inv[sa[i]] = max_num - 1;
    }
    if (max_num == n) break;
  }
  int sz = 0;
  for (int i = 0; i < n; i++) {
    if (sz > 0) sz--;
    if (sa_inv[i] == 0) continue;
    for (int j = sa[sa_inv[i] - 1];
         max(i, j) + sz < n && s[i + sz] == s[j + sz];)
      sz++;
    lcp[sa_inv[i] - 1] = sz;
  }
  return {sa, sa_inv, lcp};
}
//! @code
//!   RMQ rmq1(a, ranges::min); // -std=c++20
//!   RMQ rmq2(a, [&](auto& x, auto& y) {
//!     return min(x, y);
//!   });
//!   vector<RMQ<int, function<int(int, int)>>>
//!     rmqs(3, {{}, NULL});
//!   rmqs[1] = {a, ranges::min};
//! @endcode
//! @time O(nlogn + q)
//! @space O(nlogn)
template<class T, class F> struct RMQ {
  vector<vector<T>> dp;
  F op;
  RMQ(const vector<T>& a, F a_op): dp(1, a), op(a_op) {
    for (int i = 0; (2 << i) <= ssize(a); i++) {
      dp.emplace_back(ssize(a) - (2 << i) + 1);
      transform(begin(dp[i]), end(dp[i]) - (1 << i),
        begin(dp[i]) + (1 << i), begin(dp[i + 1]), op);
    }
  }
  T query(int l, int r) { // [l, r)
    assert(l < r);
    int lg = __lg(r - l);
    return op(dp[lg][l], dp[lg][r - (1 << lg)]);
  }
};
//! for all i in [sa_le,sa_ri):
//!   - t==s.substr(sa[i],sz(t))
//!   - `sa_ri-sa_le` is the # of matches of t in s.
//!
//! if sa_le==sa_ri then:
//!   s[s_l,s_r) is longest substring such that:
//!   s[s_l,s_r) == t[0,s_r-s_l)
struct match {
  int sa_le, sa_ri, s_l, s_r;
};
//! @code
//!   sa_query saq(s, get_sa(s, 256));
//! @endcode
template<class T> struct sa_query {
  T s;
  int n;
  vector<int> sa, sa_inv, lcp;
  RMQ<int, function<int(int, int)>> rmq;
  sa_query(const T& a_s, const array<vector<int>, 3>& d):
    s(a_s), n(ssize(s)), sa(d[0]), sa_inv(d[1]), lcp(d[2]),
    rmq(lcp, [](int x, int y) { return min(x, y); }) {}
  sa_query(const T& a_s, int max_val):
    sa_query(a_s, get_sa(a_s, max_val)) {}
  //! returns max integer k such that
  //!   s.substr(i1, k) == s.substr(i2, k)
  //! @time O(1)
  //! @space O(1)
  int len_lcp(int i1, int i2) {
    if (i1 == i2) return n - i1;
    auto [l, r] = minmax(sa_inv[i1], sa_inv[i2]);
    return rmq.query(l, r);
  }
  //! @code
  //!   int cmp2 = saq.cmp_sufs(l1,l2);
  //! @endcode
  //! requires l1,l2 < n
  //! if cmp2<0 then s[l1,n) < s[l2,n)
  //! if cmp2=0 then s[l1,n) = s[l2,n)
  //! if cmp2>0 then s[l1,n) > s[l2,n)
  //! @time O(1)
  //! @space O(1)
  int cmp_sufs(int l1, int l2) {
    return sa_inv[l1] - sa_inv[l2];
  }
  //! @code
  //!   int cmp1 = saq.cmp_substrs(l1,r1,l2,r2);
  //! @endcode
  //! requires l1,l2 < n
  //! if cmp1<0 then s[l1,r1) < s[l2,r2)
  //! if cmp1=0 then s[l1,r1) = s[l2,r2)
  //! if cmp1>0 then s[l1,r1) > s[l2,r2)
  //! @time O(1)
  //! @space O(1)
  int cmp_substrs(int l1, int r1, int l2, int r2) {
    int len1 = r1 - l1, len2 = r2 - l2;
    return len_lcp(l1, l2) >= min(len1, len2)
      ? len1 - len2
      : cmp_sufs(l1, l2);
  }
  //! https://github.com/yosupo06/Algorithm/blob/master/src/string/suffixarray.hpp
  //! returns range [l,r) such that:
  //!   - for all i in [l,r): t==s.substr(sa[i],sz(t))
  //!   - `r-l` is the # of matches of t in s.
  //! @time O(|t| * log(|s|))
  //! @space O(1)
  pair<int, int> find_str(const T& t) {
    int l = lower_bound(begin(sa), end(sa), 0,
              [&](int i, int) -> bool {
                return lexicographical_compare(
                  i + begin(s), end(s), begin(t), end(t));
              }) -
      begin(sa);
    int r = lower_bound(l + begin(sa), end(sa), 0,
              [&](int i, int) -> bool {
                return mismatch(begin(t), end(t),
                         i + begin(s), end(s))
                         .first == end(t);
              }) -
      begin(sa);
    return {l, r};
  }
  //! https://stackoverflow.com/a/11374737
  //! https://codeforces.com/blog/entry/133051
  //! @time O(log(|s|) + |t|)
  //! @space O(1)
  match find_str_fast(const T& t) {
    int s_l = n, s_len = 0;
    auto cmp = [&](int i, int) -> bool {
      if (int lcp_len = s_l == n ? 0 : len_lcp(s_l, i);
          lcp_len != s_len)
        return (lcp_len < s_len) ^ (cmp_sufs(s_l, i) < 0);
      auto [it_s, it_t] = mismatch(i + s_len + begin(s),
        end(s), s_len + begin(t), end(t));
      s_l = i, s_len = it_t - begin(t);
      return lexicographical_compare(it_s, end(s), it_t,
        end(t));
    };
    int sa_le = lower_bound(begin(sa), end(sa), 0, cmp) -
      begin(sa),
        sa_ri = sa_le;
    if (s_len == ssize(t))
      sa_ri = lower_bound(sa_le + begin(sa), end(sa), 0,
                [&](int i, int) -> bool {
                  return len_lcp(s_l, i) >= ssize(t);
                }) -
        begin(sa);
    return {sa_le, sa_ri, s_l, s_l + s_len};
  }
  //! @code
  //!   auto [sa_le,sa_ri] = saq.find_substr(s_l,s_r);
  //! @endcode
  //! requires s_l < n
  //! for all i in [sa_le,sa_ri): s.substr(s_l,s_r-s_l)
  //!   == s.substr(sa[i],s_r-s_l)
  //!   - `r-l` is the # of matches of
  //!       s.substr(s_l, s_r - s_l) in s.
  //! @time O(log(|s|))
  //! @space O(1)
  pair<int, int> find_substr(int s_l, int s_r) {
    auto cmp = [&](int i, bool flip) -> bool {
      return flip ^ (len_lcp(i, s_l) < s_r - s_l);
    };
    int l = lower_bound(begin(sa), begin(sa) + sa_inv[s_l],
              0, cmp) -
      begin(sa);
    int r = lower_bound(sa_inv[s_l] + 1 + begin(sa),
              end(sa), 1, cmp) -
      begin(sa);
    return {l, r};
  }
  //! @param substrs this defines query string t as:
  //!     s.substr(substrs[0][0], substrs[0][1] -
  //!     substrs[0][0]) + s.substr(substrs[1][0],
  //!     substrs[1][1] - substrs[1][0]) +
  //!     ...
  //!     s.substr(substrs.back()[0], substrs.back()[1] -
  //!     substrs.back()[0])
  //!     - doesn't work when substrs[i][0] == n
  //! @returns see match
  //! @time O(sz(substrs) * log(|s|))
  //! @space O(1)
  match find_substrs_concated(
    const vector<pair<int, int>>& substrs) {
    using dt = array<int, 3>;
    int sa_le = 0, sa_ri = n, s_l = 0, s_r = 0,
        sum_len = 0;
    auto cmp = [&](int i, const dt& x) -> bool {
      int j = i + sum_len,
          lcp_len =
            j == n ? 0 : min(len_lcp(j, x[0]), x[1]);
      if (lcp_len + sum_len > s_r - s_l)
        s_l = i, s_r = j + lcp_len;
      if (lcp_len < min(n - j, x[1]))
        return sa_inv[j] - sa_inv[x[0]] < x[2];
      return x[2] ^ (n - j < x[1]);
    };
    for (auto [l, r] : substrs) {
      sa_le = lower_bound(begin(sa) + sa_le,
                begin(sa) + sa_ri, dt{l, r - l, 0}, cmp) -
        begin(sa);
      sa_ri = lower_bound(begin(sa) + sa_le,
                begin(sa) + sa_ri, dt{l, r - l, 1}, cmp) -
        begin(sa);
      sum_len += r - l;
    }
    return {sa_le, sa_ri, s_l, s_r};
  }
};
