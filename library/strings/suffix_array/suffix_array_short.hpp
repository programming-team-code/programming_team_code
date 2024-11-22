#pragma once
//! https://github.com/atcoder/ac-library/blob/master/atcoder/string.hpp
//! @code
//!   // requires s[i]>=0
//!   auto [sa2, sa_inv2, lcp2] = sa_short(s);
//! @endcode
//! runs in ~1.5s for 5e5
//! @time O(n * log^2(n))
//! @space O(n)
template<class T> array<vi, 3> sa_short(const T& s) {
  int n = sz(s);
  vi sa(n), sa_inv(all(s)), lcp(n - 1);
  iota(all(sa), 0);
  for (int k = 1; k <= n; k *= 2) {
    vi x(sa_inv);
    auto proj = [&](int i) {
      return pair(x[i], i + k < n ? x[i + k] : -1);
    };
    ranges::sort(sa, {}, proj);
    sa_inv[sa[0]] = 0;
    rep(i, 1, n) sa_inv[sa[i]] =
      sa_inv[sa[i - 1]] + (proj(sa[i - 1]) != proj(sa[i]));
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
