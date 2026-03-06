#pragma once
#include "../math/mod_division.hpp"
//! https://codeforces.com/blog/entry/127823
//! @code
//!   vi c = xor_conv(a, b);
//!   // must have sz(a) == sz(b) == a power of 2
//!   // c[k] = sum of a[i]*b[j] where i^j==k
//! @endcode
//! @time O(n log n)
//! @space O(n)
void fwht(int n, vi& a) {
  for (int i = 1; i < n; i *= 2)
    for (int j = 0; j < n; j += 2 * i) rep(k, 0, i) {
        int x = a[j + k], y = a[i + j + k];
        a[j + k] = (x + y) % mod;
        a[i + j + k] = (x - y + mod) % mod;
      }
}
vi xor_conv(vi a, vi b) {
  int n = sz(a), inv = mod_div(1, n);
  fwht(n, a);
  fwht(n, b);
  vi res(n);
  rep(i, 0, n) res[i] = 1LL * a[i] * b[i] % mod;
  fwht(n, res);
  rep(i, 0, n) res[i] = 1LL * res[i] * inv % mod;
  return res;
}
