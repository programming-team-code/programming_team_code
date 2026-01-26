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
  const int n = sz(s), K = 4;
  vi sa(n), sa_inv(all(s)), lcp(n - 1);
  iota(all(sa), 0);
  for (int j = 1; j <= n; j *= K) {
    vi x(sa_inv), y(lcp);
    auto f = [&](int i) {
      array<int, K> res;
      rep (k, 0, K)
        res[k] = i + j * k < n ? x[i + j * k] : -1;
      return res;
    };
    ranges::sort(sa, {}, f);
    sa_inv[sa[0]] = 0;
    rep(i, 0, n - 1) {
      sa_inv[sa[i + 1]] = sa_inv[sa[i]];
      if (f(sa[i + 1]) != f(sa[i])) {
        sa_inv[sa[i + 1]]++;
        rep (k, 0, K) {
          if (f(sa[i + 1])[k] != f(sa[i])[k]) {
            lcp[i] = j * k + (sa[i] + j * k < n ? y[x[sa[i] + j * k]] : 0);
            break;
          }
        }
      } else {
        lcp[i] = min({j * K, n - sa[i], n - sa[i + 1]});
      }
    }
  }
  return tuple{sa, sa_inv, lcp};
}
