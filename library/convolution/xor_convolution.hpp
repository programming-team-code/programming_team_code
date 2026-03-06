#pragma once
#include "../math/mod_division.hpp"
void fwht(int n, vi& a) {
  for (int i = 1; i != n; i <<= 1)
    for (int j = 0; j != n; j += i << 1)
      for (int k = 0; k != i; k++) {
        int x = a[j + k], y = a[i + j + k];
        a[j + k] = (x + y) % mod;
        a[i + j + k] = (x - y + mod) % mod;
      }
}
vi xor_conv(vi& a, vi& b) {
  int n = sz(a), inv = mod_div(1, n);
  fwht(n, a);
  fwht(n, b);
  vi res(n);
  rep(i, 0, n) res[i] = 1LL * a[i] * b[i] % mod;
  fwht(n, res);
  rep(i, 0, n) res[i] = 1LL * res[i] * inv % mod;
  return res;
}
