#pragma once
//! https://github.com/atcoder/ac-library/blob/master/atcoder/string.hpp
//! @code
//!   // requires s[i]>=0
//!   string s;
//!   auto [sa, sa_inv, lcp] = sa_short(s);
//!   vi s_vec;
//!   auto [sa1, sa_inv1, lcp1] = sa_short(s_vec);
//! @endcode
//! runs in ~1.5s for 5e5
//! @time O(n * log^2(n))
//! @space O(n)
auto sa_short(const auto& s) {
  const int K = 4;
  int n = sz(s);
  vi sa(n), sa_inv(all(s)), lcp(n - 1);
  iota(all(sa), 0);
  for (int j = 1; j <= n; j *= K) {
    vi x(sa_inv);
    auto proj = [&](int i) {
      array<int, K> res;
      rep (k, 0, K)
        res[k] = i + j * k < n ? x[i + j * k] : -1;
      return res;
      //return pair(x[i], i + j < n ? x[i + j] : -1);
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
  return tuple{sa, sa_inv, lcp};
}
