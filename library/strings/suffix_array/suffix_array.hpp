#pragma once
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
//!   // requires 0<=s[i]<max_num
//!   string s;
//!   auto [sa, sa_inv, lcp] = get_sa(s, 256);
//!   vi s_vec;
//!   auto [sa1, sa_inv1, lcp1] = get_sa(s_vec, 100'001);
//! @endcode
//!
//! @time O(nlogn + max_num)
//! @space O(n + max_num)
auto get_sa(const auto& s, int max_num) {
  int n = sz(s);
  vi sa(n), sa_inv(all(s)), lcp(n - 1);
  iota(all(sa), 0);
  for (int i = 0; i < n; i = max(1, 2 * i)) {
    vi y(sa_inv), freq(max_num);
    iota(all(sa_inv), n - i);
    ranges::copy_if(sa, begin(sa_inv) + i,
      [&](int& x) { return (x -= i) >= 0; });
    for (int x : y) freq[x]++;
    partial_sum(all(freq), begin(freq));
    for (int x : sa_inv | views::reverse)
      sa[--freq[y[x]]] = x;
    max_num = 1, sa_inv[sa[0]] = 0;
    auto prev_inv = [&](int j) {
      return pair(y[j], i + j < n ? y[i + j] : -1);
    };
    rep(j, 1, n) {
      max_num += prev_inv(sa[j - 1]) != prev_inv(sa[j]);
      sa_inv[sa[j]] = max_num - 1;
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
  return tuple{sa, sa_inv, lcp};
}
