/** @file */
#pragma once
const int mod = 998'244'353;
/**
 * @param a,b arrays of the same length, where the length is a power of 2
 * @returns array `c` where `c[k]` = the sum of (a[i] * b[j]) for all pairs
 * (i,j) where i ^ j == k
 * @time O(2^n * n)
 * @space a size O(2^n) vector is allocated and returned
 */
vi xor_convolution(vi a, vi b) {
  int n = __lg(sz(a));
  assert(sz(a) == sz(b) && (1 << n) == sz(a));
  for (int pw = n - 1; pw >= 0; pw--) {
    for (int i = 0; i < (1 << n); i += 1 << (pw + 1)) {
      rep(j, i, i + (1 << pw)) {
        int x, y, k = j + (1 << pw);
        x = a[j], y = a[k];
        a[j] = (x + y) % mod, a[k] = (x - y + mod) % mod;
        x = b[j], y = b[k];
        b[j] = (x + y) % mod, b[k] = (x - y + mod) % mod;
      }
    }
  }
  vi c(1 << n);
  rep(i, 0, 1 << n) { c[i] = 1LL * a[i] * b[i] % mod; }
  rep(pw, 0, n) {
    for (int i = 0; i < (1 << n); i += 1 << (pw + 1)) {
      rep(j, i, i + (1 << pw)) {
        int k = j + (1 << pw);
        int x = c[j], y = c[k];
        c[j] = (x + y) % mod, c[k] = (x - y + mod) % mod;
      }
    }
  }
  const int inv2 = (mod + 1) / 2;
  int inv = 1;
  rep(pw, 0, n) { inv = 1LL * inv * inv2 % mod; }
  rep(i, 0, 1 << n) { c[i] = 1LL * c[i] * inv % mod; }
  return c;
}
