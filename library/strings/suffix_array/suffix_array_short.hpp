#pragma once
//! https://github.com/atcoder/ac-library/blob/master/atcoder/string.hpp
//! @code
//!   // requires s[i]>=0
//!   string s;
//!   auto [sa, sa_inv, lcp] = sa_short(s);
//!   vi s_vec;
//!   auto [sa1, sa_inv1, lcp1] = sa_short(s_vec);
//! @endcode
//! runs in ~0.5s for 5e5
//! @time O(n * log^2(n))
//! @space O(n)
auto sa_short(const auto& s) {
  const int n = sz(s), b = 6;
  vi sa(n), sa_inv(all(s)), lcp(n - 1);
  iota(all(sa), 0);
  for (int j = 1; j <= n; j *= b) {
    vi x(sa_inv);
    auto cmp = [&](int i1, int i2) {
      rep(k, 0, b) {
        int a = i1 + j * k < n ? x[i1 + j * k] : -1;
        int b = i2 + j * k < n ? x[i2 + j * k] : -1;
        if (a != b) return a < b;
      }
      return false;
    };
    sort(all(sa), cmp);
    sa_inv[sa[0]] = 0;
    rep(i, 1, n) sa_inv[sa[i]] =
      sa_inv[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
  }
  int l = 0;
  rep(i, 0, n) {
    if (l > 0) l--;
    if (sa_inv[i] == 0) continue;
    int j = sa[sa_inv[i] - 1];
    while (max(i, j) + l < n && s[i + l] == s[j + l]) l++;
    lcp[sa_inv[i] - 1] = l;
  }
  return tuple{sa, sa_inv, lcp};
}
