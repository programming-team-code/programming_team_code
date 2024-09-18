#pragma once
//! @see https://github.com/kth-competitive-programming/kactl/blob/main/content/strings/SuffixArray.h
//! suffixes of "banana":
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
//! sa_inv = {3, 2, 5, 1, 4, 0} (sa[sa_inv[i]] == i, sa_inv[sa[i]] == i)
//! lcp = {1, 3, 0, 0, 2}
//!
//! @code{.cpp}
//!     string s;
//!     auto [sa, sa_inv, lcp] = get_sa(s, 256);
//!     // or
//!     vi a;
//!     auto [sa, sa_inv, lcp] = get_sa(a, 100'005);
//! @endcode
//!
//! @param s,max_num string/array with 0 <= s[i] < max_num
//! @returns sa, sa_inv, lcp
//! @time O(nlogn + max_num)
//! @space vectors `sa`, `sa_inv`, `lcp` are O(n). vector `freq` is O(max_num) and is allocated temporarily
template<class T>
array<vi, 3> get_sa(const T& s, int max_num) {
  int n = sz(s);
  vi sa(n), sa_inv(all(s)), lcp(max(0, n - 1));
  iota(all(sa), 0);
  for (int ln = 0; ln < n; ln = max(1, 2 * ln)) {
    vi tmp(n), freq(max_num);
    iota(begin(tmp), begin(tmp) + ln, n - ln);
    copy_if(all(sa), begin(tmp) + ln,
      [&](int& x) { return (x -= ln) >= 0; });
    for (int x : sa_inv) freq[x]++;
    partial_sum(all(freq), begin(freq));
    for_each(rbegin(tmp), rend(tmp),
      [&](int x) { sa[--freq[sa_inv[x]]] = x; });
    swap(sa_inv, tmp);
    max_num = 1, sa_inv[sa[0]] = 0;
    auto prev_inv = [&](int i) {
      return pair(tmp[i], i + ln < n ? tmp[i + ln] : -1);
    };
    rep(i, 1, n) {
      max_num += prev_inv(sa[i - 1]) != prev_inv(sa[i]);
      sa_inv[sa[i]] = max_num - 1;
    }
    if (max_num == n) break;
  }
  int sz = 0;
  rep(i, 0, n) {
    if (sz > 0) sz--;
    if (sa_inv[i] == 0) continue;
    for (int j = sa[sa_inv[i] - 1];
         max(i, j) + sz < n && s[i + sz] == s[j + sz];)
      sz++;
    lcp[sa_inv[i] - 1] = sz;
  }
  return {sa, sa_inv, lcp};
}
