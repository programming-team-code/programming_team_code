#pragma once
//! @code
//!   auto lcm_conv = lcm_convolution(a, b);
//! @endcode
//! ssize(a)==ssize(b)
//! lcm_conv[k] = sum of (a[i]*b[j])
//!   for all pairs (i,j) where lcm(i,j)==k
//! @time O(n log n)
//! @space O(n)
const int mod = 998'244'353;
vi lcm_convolution(const vi& a, const vi& b) {
  int n = sz(a);
  vector<ll> sum_a(n), sum_b(n);
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
