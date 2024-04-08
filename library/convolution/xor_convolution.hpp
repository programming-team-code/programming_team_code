/** @file */
#pragma once
const int mod = 998'244'353;
// change this
int inverse(int x) {
  return x == 1 ? 1 : mod - mod / x * inverse(mod % x) % mod;
}
/**
 * @param a,b arrays of the same length, where the length is a power of 2
 * @returns array `c` where `c[k]` = the sum of (a[i] * b[j]) for all pairs
 * (i,j) where i ^ j == k
 * @time O(2^n * n)
 * @space a size O(2^n) vector is allocated and returned
 */
vector<int> xor_convolution(vector<int> a, vector<int> b) {
  int n = __lg(sz(a));
  assert(sz(a) == sz(b) && (1 << n) == sz(a));
  for (int pw = n - 1; pw >= 0; pw--) {
    for (int i = 0; i < (1 << n); i += 1 << (pw + 1)) {
      for (int j = i; j < i + (1 << pw); j++) {
        int x, y, k = j + (1 << pw);
        x = a[j], y = a[k];
        a[j] = (x + y) % mod, a[k] = (x - y + mod) % mod;
        x = b[j], y = b[k];
        b[j] = (x + y) % mod, b[k] = (x - y + mod) % mod;
      }
    }
  }
  vector<int> c(1 << n);
  for (int i = 0; i < (1 << n); i++) {
    c[i] = 1LL * a[i] * b[i] % mod;
  }
  for (int pw = 0; pw < n; pw++) {
    for (int i = 0; i < (1 << n); i += 1 << (pw + 1)) {
      for (int j = i; j < i + (1 << pw); j++) {
        int k = j + (1 << pw);
        int x = c[j], y = c[k];
        c[j] = (x + y) % mod, c[k] = (x - y + mod) % mod;
      }
    }
  }
  const int inv = inverse(1 << n);
  for (int i = 0; i < (1 << n); i++) {
    c[i] = 1LL * c[i] * inv % mod;
  }
  return c;
}
