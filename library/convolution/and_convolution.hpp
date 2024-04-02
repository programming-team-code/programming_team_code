/** @file */
#pragma once
const int mod = 998'244'353;
/**
 * @param a,b arrays of the same length, where the length is a power of 2
 * @returns array `c` where `c[k]` = the sum of (a[i] * b[j]) for all pairs
 * (i,j) where i & j == k
 * @time O(2^n * n)
 * @space a size O(2^n) vector is allocated and returned
 */
vi and_convolution(vi a, vi b) {
  int n = __lg(sz(a));
  assert(sz(a) == sz(b) && (1 << n) == sz(a));
  rep (i, 0, n)
    rep (j, 0, (1 << n))
      if (!((j >> i) & 1)) {
        a[j] = (a[j] + a[j ^ (1 << i)]) % mod;
        b[j] = (b[j] + b[j ^ (1 << i)]) % mod;
      }
  vi c(1 << n);
  rep (i, 0, (1 << n))
    c[i] = 1LL * a[i] * b[i] % mod;
  rep (i, 0, n)
    rep (j, 0, (1 << n))
      if (!((j >> i) & 1))
        c[j] = (c[j] - c[j ^ (1 << i)] + mod) % mod;
  return c;
}
