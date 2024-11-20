#pragma once
//! https://github.com/atcoder/ac-library/blob/master/atcoder/string.hpp
//! @code
//!   auto [sa, sa_inv, lcp] = sa_short(s);
//! @endcode
//! runs in ~1.5s for 5e5
//! @time O(nlogn)
//! @space O(n)
template<class T> array<vi, 2> sa_short(const T& s) {
  int n = int(s.size());
  vi sa(n), sa_inv(all(s));
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
  return {sa, sa_inv};
}
