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
const int mn = '0',
          cnt_let =
            36; // mn <= s[i] < mn + cnt_let; for lowercase
                // letters: mn = 'a', cnt_let = 26
//! Burrows Wheeler transform
struct bwt {
  int n;
  char last;
  vector<array<int, cnt_let>> occ;
  array<int, cnt_let + 1> cnt{};
  //! @code
  //!     string s;
  //!     auto [_, __, sa, sa_inv, lcp, ___] =
  //!     suffix_array(s, 256); bwt bw(s, sa);
  //! @endcode
  //! @param s,sa a string and its suffix array
  //! @time O(n * cnt_let)
  //! @space O(n * cnt_let) for `occ` vector; it's possible
  //! to improve this
  //!     to O(n * cnt_let / 64)
  //!     https://codeforces.com/contest/963/submission/217802614
  bwt(const string& s, const vector<int>& sa):
    n(ssize(s)), last(empty(s) ? -1 : s.back() - mn),
    occ(n + 1) {
    for (int i = 0; i < n; i++) {
      cnt[s[i] + 1 - mn]++;
      occ[i + 1] = occ[i];
      if (sa[i] == 0) continue;
      occ[i + 1][s[sa[i] - 1] - mn]++;
    }
    partial_sum(begin(cnt), end(cnt), begin(cnt));
  }
  //! @param t query string
  //! @returns vectors `l`, `r` where given `t_le` (0 <=
  //! t_le <= |t|) defines a suffix [t_le, |t|) of t:
  //!     - for all i in [l[t_le], r[t_le]):
  //!     t.substr(t_le)
  //!     == s.substr(sa[i], sz(t) - t_le)
  //!     - `r[t_le] - l[t_le]` is the # of matches of
  //!     t.substr(t_le) in s. note: r[t_le] - l[t_le] <=
  //!     r[t_le + 1] - l[t_le + 1]
  //! @time O(|t|)
  //! @space 2 O(|t|) vectors are allocated and returned
  array<vector<int>, 2> find_str(const string& t) {
    vector<int> l(ssize(t) + 1, 0), r(ssize(t) + 1, n);
    for (int i = ssize(t) - 1; i >= 0; i--) {
      char c = t[i] - mn;
      l[i] = cnt[c] + occ[l[i + 1]][c] +
        (c == last && i < ssize(t) - 1);
      r[i] = cnt[c] + occ[r[i + 1]][c] + (c == last);
    }
    return {l, r};
  }
};
