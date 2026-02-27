//! @code
//!   auto gcd_conv = gcd_convolution(a, b);
//! @endcode
//! sz(a)==sz(b)
//! gcd_conv[k] = sum of (a[i]*b[j])
//!   for all pairs (i,j) where gcd(i,j)==k
//! @time O(n log n)
//! @space O(n)
const int mod = 998'244'353;
vector<int> gcd_convolution(const vector<int>& a,
  const vector<int>& b) {
  int n = ssize(a);
  vector<int> c(n);
  for (int g = n - 1; g >= 1; g--) {
    int64_t sum_a = 0, sum_b = 0;
    for (int i = g; i < n; i += g) {
      sum_a += a[i], sum_b += b[i];
      if ((c[g] -= c[i]) < 0) c[g] += mod;
    }
    sum_a %= mod, sum_b %= mod;
    c[g] = (c[g] + sum_a * sum_b) % mod;
  }
  return c;
}
