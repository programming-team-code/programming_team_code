/** @file */
#pragma once
const int mod = 998'244'353;
/**
 * @param a,b arrays of the same length
 * @returns array `c` where `c[k]` = the sum of (a[i] * b[j]) for all pairs
 * (i,j) where lcm(i,j) == k
 * @time O(n log n)
 * @space this function allocates/returns various O(n) vectors
 */
vi lcm_convolution(const vi& a, const vi& b) {
  assert(sz(a) == sz(b));
  int n = sz(a);
  vector sum_a(n, 0LL), sum_b(n, 0LL);
  vi c(n);
  rep(i, 1, n) {
    for (int j = i; j < n; j += i)
      sum_a[j] += a[i], sum_b[j] += b[i];
    sum_a[i] %= mod, sum_b[i] %= mod;
    c[i] = (c[i] + sum_a[i] * sum_b[i]) % mod;
    for (int j = i + i; j < n; j += i)
      if ((c[j] -= c[i]) < 0) c[j] += mod;
  }
  return c;
}
