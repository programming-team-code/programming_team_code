#pragma once
//! @code
//!   auto gcd_conv = gcd_convolution(a, b);
//! @endcode
//! sz(a)==sz(b)
//! gcd_conv[k] = sum of (a[i]*b[j])
//!   for all pairs (i,j) where gcd(i,j)==k
//! @time O(n log n)
//! @space O(n)
constexpr int mod = 998'244'353;
vi gcd_convolution(const vi& a, const vi& b) {
  int n = sz(a);
  vi c(n);
  for (int g = n - 1; g >= 1; g--) {
    ll sum_a = 0, sum_b = 0;
    for (int i = g; i < n; i += g) {
      sum_a += a[i], sum_b += b[i];
      if ((c[g] -= c[i]) < 0) c[g] += mod;
    }
    sum_a %= mod, sum_b %= mod;
    c[g] = (c[g] + sum_a * sum_b) % mod;
  }
  return c;
}
