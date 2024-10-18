//! @code
//!   auto mono_le1 = mono_st(a, less());
//!   // less_equal(), greater(), greater_equal()
//! @endcode
//! when cmp == less():
//!   a[mono_le1[i]] < a[i]
//! @time O(n)
//! @space O(n)
template<class T, class F>
vector<int> mono_st(const vector<T>& a, F cmp) {
  vector<int> le((int)size(a));
  for (int i = 0; i < ((int)size(a)); i++)
    for (le[i] = i - 1;
         le[i] >= 0 && !cmp(a[le[i]], a[i]);)
      le[i] = le[le[i]];
  return le;
}
//! @code
//!   auto mono_le2 = mono_st(a, less());
//!   auto mono_ri2 = mono_range(mono_le2);
//!   // less_equal(), greater(), greater_equal()
//! @endcode
//! when cmp == less():
//!   a[mono_le2[i]] < a[i] >= a[mono_ri2[i]]
//! @time O(n)
//! @space O(n)
vector<int> mono_range(const vector<int>& le) {
  vector<int> ri((int)size(le), (int)size(le));
  for (int i = 0; i < ((int)size(le)); i++)
    for (int j = i - 1; j != le[i]; j = le[j]) ri[j] = i;
  return ri;
}
//!   when cmp is less():
//!   a = {2, 1, 3, 1, 1, 0, 1, 2, 2, 0, 2}
//!       (---------------------------x---)
//!       (------------x)   (x------) | (x)
//!       (x)   (x)    |     | (---x) |  |
//!        |     |     |     |     |  |  |
//! index: 0  1  2  3  4  5  6  7  8  9  10
//!
//! nodes are the right-most min/max of their subarray:
//! p[0] = p[2] = 4
//! p[8] = 6
//! p[4] = p[6] = p[10] = 9
//! p[9] = -1 (root)
//!
//! indexes 1, 3, 5, 7 are not nodes; here p maps i to
//! right-most min/max in their subarray: p[1] = p[3] = 4
//! p[7] = 8
//! p[5] = 9
//!
//! @code
//!     auto le = mono_st(a, less()), p =
//!     cart_k_ary_tree(a, le); // min cart tree auto le =
//!     mono_st(a, greater()), p = cart_k_ary_tree(a, le);
//!     // max cart tree bool is_node = (p[i] < i || a[i]
//!     != a[p[i]]);
//! @endcode
//!
//! @param a,le array and its left-monotonic stack
//! @returns parent array
//! @time O(n)
//! @space a O(n) vector is allocated and returned
template<class T>
vector<int> cart_k_ary_tree(const vector<T>& a,
  const vector<int>& le) {
  vector<int> p(le);
  for (int i = (int)size(a) - 1; i >= 0; i--)
    for (int j = i - 1; j != le[i]; j = le[j])
      if (le[j] == le[i] || a[i] == a[le[j]])
        p[j] = (p[i] < i || a[i] != a[p[i]] ? i : p[i]);
  return p;
}
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
  int n = (int)size(s);
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
    for (int i = 0; (2 << i) <= (int)size(a); i++) {
      dp.emplace_back((int)size(a) - (2 << i) + 1);
      transform(begin(dp[i]), end(dp[i]) - (1 << i),
        begin(dp[i]) + (1 << i), begin(dp[i + 1]), op);
    }
  }
  T query(int le, int ri) { // [le, ri)
    assert(le < ri);
    int lg = __lg(ri - le);
    return op(dp[lg][le], dp[lg][ri - (1 << lg)]);
  }
};
//! for all i in [sa_le,sa_ri):
//!   - t==s.substr(sa[i],sz(t))
//!   - `sa_ri-sa_le` is the # of matches of t in s.
//!
//! if sa_le==sa_ri then:
//!   s[s_le,s_ri) is longest substring such that:
//!   s[s_le,s_ri) == t[0,s_ri-s_le)
struct match {
  int sa_le, sa_ri, s_le, s_ri;
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
    s(a_s), n((int)size(s)), sa(d[0]), sa_inv(d[1]),
    lcp(d[2]),
    rmq(lcp, [](int x, int y) { return min(x, y); }) {}
  sa_query(const T& a_s, int max_val):
    sa_query(a_s, get_sa(a_s, max_val)) {}
  //! returns max integer k such that
  //!   s.substr(i1, k) == s.substr(i2, k)
  //! @time O(1)
  //! @space O(1)
  int len_lcp(int i1, int i2) {
    if (i1 == i2) return n - i1;
    auto [le, ri] = minmax(sa_inv[i1], sa_inv[i2]);
    return rmq.query(le, ri);
  }
  //! @code
  //!   int cmp2 = saq.cmp_sufs(le1,le2);
  //! @endcode
  //! requires le1,le2 < n
  //! if cmp2<0 then s[le1,n) < s[le2,n)
  //! if cmp2=0 then s[le1,n) = s[le2,n)
  //! if cmp2>0 then s[le1,n) > s[le2,n)
  //! @time O(1)
  //! @space O(1)
  int cmp_sufs(int le1, int le2) {
    return sa_inv[le1] - sa_inv[le2];
  }
  //! @code
  //!   int cmp1 = saq.cmp_substrs(le1,ri1,le2,ri2);
  //! @endcode
  //! requires le1,le2 < n
  //! if cmp1<0 then s[le1,ri1) < s[le2,ri2)
  //! if cmp1=0 then s[le1,ri1) = s[le2,ri2)
  //! if cmp1>0 then s[le1,ri1) > s[le2,ri2)
  //! @time O(1)
  //! @space O(1)
  int cmp_substrs(int le1, int ri1, int le2, int ri2) {
    int len1 = ri1 - le1, len2 = ri2 - le2;
    return len_lcp(le1, le2) >= min(len1, len2)
      ? len1 - len2
      : cmp_sufs(le1, le2);
  }
  //! https://github.com/yosupo06/Algorithm/blob/master/src/string/suffixarray.hpp
  //! returns range [le,ri) such that:
  //!   - for all i in [le,ri): t==s.substr(sa[i],sz(t))
  //!   - `ri-le` is the # of matches of t in s.
  //! @time O(|t| * log(|s|))
  //! @space O(1)
  pair<int, int> find_str(const T& t) {
    int le = lower_bound(begin(sa), end(sa), 0,
               [&](int i, int) -> bool {
                 return lexicographical_compare(
                   i + begin(s), end(s), begin(t), end(t));
               }) -
      begin(sa);
    int ri = lower_bound(le + begin(sa), end(sa), 0,
               [&](int i, int) -> bool {
                 return mismatch(begin(t), end(t),
                          i + begin(s), end(s))
                          .first == end(t);
               }) -
      begin(sa);
    return {le, ri};
  }
  //! https://stackoverflow.com/a/11374737
  //! https://codeforces.com/blog/entry/133051
  //! @time O(log(|s|) + |t|)
  //! @space O(1)
  match find_str_fast(const T& t) {
    int s_le = n, s_len = 0;
    auto cmp = [&](int i, int) -> bool {
      if (int lcp_len = s_le == n ? 0 : len_lcp(s_le, i);
          lcp_len != s_len)
        return (lcp_len < s_len) ^ (cmp_sufs(s_le, i) < 0);
      auto [it_s, it_t] = mismatch(i + s_len + begin(s),
        end(s), s_len + begin(t), end(t));
      s_le = i, s_len = it_t - begin(t);
      return lexicographical_compare(it_s, end(s), it_t,
        end(t));
    };
    int sa_le = lower_bound(begin(sa), end(sa), 0, cmp) -
      begin(sa),
        sa_ri = sa_le;
    if (s_len == (int)size(t))
      sa_ri = lower_bound(sa_le + begin(sa), end(sa), 0,
                [&](int i, int) -> bool {
                  return len_lcp(s_le, i) >= (int)size(t);
                }) -
        begin(sa);
    return {sa_le, sa_ri, s_le, s_le + s_len};
  }
  //! @code
  //!   auto [sa_le,sa_ri] = saq.find_substr(s_le,s_ri);
  //! @endcode
  //! requires s_le < n
  //! for all i in [sa_le,sa_ri): s.substr(s_le,s_ri-s_le)
  //!   == s.substr(sa[i],s_ri-s_le)
  //!   - `ri-le` is the # of matches of
  //!       s.substr(s_le, s_ri - s_le) in s.
  //! @time O(log(|s|))
  //! @space O(1)
  pair<int, int> find_substr(int s_le, int s_ri) {
    auto cmp = [&](int i, bool flip) -> bool {
      return flip ^ (len_lcp(i, s_le) < s_ri - s_le);
    };
    int le = lower_bound(begin(sa),
               begin(sa) + sa_inv[s_le], 0, cmp) -
      begin(sa);
    int ri = lower_bound(sa_inv[s_le] + 1 + begin(sa),
               end(sa), 1, cmp) -
      begin(sa);
    return {le, ri};
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
    int sa_le = 0, sa_ri = n, s_le = 0, s_ri = 0,
        sum_len = 0;
    auto cmp = [&](int i, const dt& x) -> bool {
      int j = i + sum_len,
          lcp_len =
            j == n ? 0 : min(len_lcp(j, x[0]), x[1]);
      if (lcp_len + sum_len > s_ri - s_le)
        s_le = i, s_ri = j + lcp_len;
      if (lcp_len < min(n - j, x[1]))
        return sa_inv[j] - sa_inv[x[0]] < x[2];
      return x[2] ^ (n - j < x[1]);
    };
    for (auto [le, ri] : substrs) {
      sa_le =
        lower_bound(begin(sa) + sa_le, begin(sa) + sa_ri,
          dt{le, ri - le, 0}, cmp) -
        begin(sa);
      sa_ri =
        lower_bound(begin(sa) + sa_le, begin(sa) + sa_ri,
          dt{le, ri - le, 1}, cmp) -
        begin(sa);
      sum_len += ri - le;
    }
    return {sa_le, sa_ri, s_le, s_ri};
  }
};
const int mn = '0',
          cnt_let =
            36; // mn <= s[i] < mn + cnt_let; for lowercase
                // letters: mn = 'a', cnt_let = 26
//! Replacing suffix trees with enhanced suffix arrays by
//! Mohamed Ibrahim Abouelhoda, Stefan Kurtz, Enno
//! Ohlebusch
//!
//! offline version of suffix tree, idea: min k-ary
//! cartesian tree of LCP array corresponds exactly to the
//! internal nodes of the suffix tree. Then add in <= n
//! nodes, one for each suffix, and it corresponds to the
//! suffix tree.
//!
//! string = "cabcabacaabc"
//!                                              c
//!              c                               b
//!              b               c               a
//!              a               b           c   a
//!      c       a               a           b   c
//!      b       c       c       a           a   a
//!      a       a   c   b       c           a   b
//!      a       b   b   a       a       c   c   a
//!  c   c       a   a   a       b       b   a   c
//!  b   a   c | c   a   c       a       a   b | b
//!  a   b | b | b   c   a   c | c       a | a | a
//!  a | a | a | a | a   b | b | b   c | c | c | c
//!    1   2   3   1   0   1   2   0   1   2   3   <- LCP
//! (------------------------------R--------------)
//! (--------------a--) (--b------) (--c----------)
//! (a) (--b------) (c) (a) (--c--)     (--a------)
//!     (a) (--c--)             (a)     (a) (--b--)
//!             (a)                         (a) (c)
//!
//! note leaf nodes dont exist when that suffix is a prefix
//! of a longer suffix
//!
//! @code
//!     string s;
//!     lcp_tree lt(s);
//! @endcode
//!
//! internal nodes are a subset of [0, n - 1), each
//! internal node represents:
//!     - a prefix of some suffix; in the suffix tree, each
//!     edge has some substring. This prefix of suffix
//!     corresponds to this substring
//!     - a range in the suffix array
//!     - a lcp number of this range of suffixes
//!     representing length of prefix of these suffixes
//! leaf nodes are a subset of [n - 1, 2 * n - 1), each
//! leaf represents:
//!     - a single suffix
struct lcp_tree {
  sa_query<string> sf_a;
  vector<int> le, ri;
  int root;
  vector<vector<int>> adj;
  //! @param s non-empty string/array
  //! @time O((n log n) + (mn + cnt_let) + (n * cnt_let))
  //! @space adj is O(n * cnt_let)
  lcp_tree(const string& s):
    sf_a(s, mn + cnt_let), le(mono_st(sf_a.lcp, less())),
    ri(mono_range(le)),
    adj(max(sf_a.n - 1, 0), vector(cnt_let, -1)) {
    vector<int> p = cart_k_ary_tree(sf_a.lcp, le);
    root = find(begin(p), end(p), -1) - begin(p);
    auto node = [&](int i) -> int {
      return p[i] < i || sf_a.lcp[i] != sf_a.lcp[p[i]]
        ? i
        : p[i];
    };
    for (int i = 0; i < ((int)size(p)); i++)
      if (node(i) == i && i != root)
        adj[p[i]][s[sf_a.sa[i] + sf_a.lcp[p[i]]] - mn] = i;
    for (int i = 0; i < (sf_a.n); i++) {
      int prev_lcp = (i ? sf_a.lcp[i - 1] : 0);
      int next_lcp =
        (i < (int)size(sf_a.lcp) ? sf_a.lcp[i] : -1);
      int v = (prev_lcp > next_lcp) ? i - 1 : node(i);
      int idx = sf_a.sa[i] + max(prev_lcp, next_lcp);
      if (v == -1 || idx == sf_a.n) continue;
      adj[v][s[idx] - mn] = sf_a.n - 1 + i;
    }
  }
  //! @param v node
  //! @returns range [le, ri) such that the following (ri -
  //! le) substrings are equal:
  //!     - for all i in [le, ri): s.substr(sa[i],
  //!     lcp_len(v))
  //! @time O(1)
  //! @space O(1)
  pair<int, int> sa_range(int v) {
    if (v < sf_a.n - 1) return {le[v] + 1, ri[v] + 1};
    return {v - sf_a.n + 1, v - sf_a.n + 2};
  }
  //! @param v node
  //! @returns length of longest common prefix of v's
  //! interval/range
  //! @time O(1)
  //! @space O(1)
  int len_lcp_range(int v) {
    return v < sf_a.n - 1
      ? sf_a.lcp[v]
      : sf_a.n - sf_a.sa[v - sf_a.n + 1];
  }
  //! @param v node
  //! @param c letter (don't subtract mn)
  //! @returns child of v following edge with label c, -1
  //! means child doesn't exist
  //! @time O(1)
  //! @space O(1)
  int get_child(int v, char c) {
    return v < sf_a.n - 1 ? adj[v][c - mn] : -1;
  }
  //! performs trie-style downwards tree walk
  //! @param t needle
  //! @returns range [le, ri) such that:
  //!     - for all i in [le, ri): t == s.substr(sa[i],
  //!     sz(t))
  //!     - `ri - le` is the # of matches of t in s.
  //! @time O(|t|)
  //! @space O(1)
  pair<int, int> find_str(const string& t) {
    int v = root;
    for (int i = 0; i < ((int)size(t)); i++) {
      if (i == len_lcp_range(v)) {
        v = get_child(v, t[i]);
        if (v == -1) return {0, 0};
      }
      int sa_le = sa_range(v).first;
      if (sf_a.s[sf_a.sa[sa_le] + i] != t[i])
        return {0, 0};
    }
    return sa_range(v);
  }
};
