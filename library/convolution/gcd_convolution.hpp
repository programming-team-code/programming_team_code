/** @file */
#pragma once
const int mod = 998'244'353;
/**
 * @param a,b arrays of the same length
 * @returns array `c` where `c[k]` = the sum of (a[i] * b[j]) for all pairs
 * (i,j) where gcd(i,j) == k
 * @time O(n log n)
 * @space a size O(n) vector is allocated and returned
 */
vector<int> gcd_convolution(const vector<int>& a, const vector<int>& b) {
  assert(ssize(a) == ssize(b));
  int n = ssize(a);
  vector<int> c(n);
  for (int g = n - 1; g >= 1; g--) {
    auto sum_a = 0LL, sum_b = 0LL;
    for (int i = g; i < n; i += g) {
      sum_a += a[i], sum_b += b[i];
      if ((c[g] -= c[i]) < 0) c[g] += mod;
    }
    sum_a %= mod, sum_b %= mod;
    c[g] = (c[g] + sum_a * sum_b) % mod;
  }
  return c;
}
