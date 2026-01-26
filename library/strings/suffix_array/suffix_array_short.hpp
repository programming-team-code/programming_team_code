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
    int val;
    auto cmp = [&](int i1, int i2) {
      val = 0;
      rep (k, 0, K) {
        int a = i1 + j * k < n ? x[i1 + j * k] : -1;
        int b = i2 + j * k < n ? x[i2 + j * k] : -1;
        if (a != b) {
          if (a != -1) val += y[a];
          else val = n - i1;
          return a < b;
        }
        val += j;
      }
      return false;
    };
    ranges::sort(sa, cmp);
    sa_inv[sa[0]] = 0;
    rep(i, 0, n - 1) {
      sa_inv[sa[i + 1]] = sa_inv[sa[i]] + cmp(sa[i], sa[i + 1]);
      lcp[i] = val;
    }
  }
  return tuple{sa, sa_inv, lcp};
}
