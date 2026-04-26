//! https://nor-blog.pages.dev/posts/2023-11-27-std-exchange-cpp/
//! @code
//!   int quotient = mod_div(x, y); // returns x * y^-1
//! @endcode
//! @time O(log(y))
//! @space O(1)
const int mod = 998244353;
int mod_div(int x, int y) {
  int m = mod, u = 1, v = 0;
  while (m) swap(u -= y / m * v, v), swap(y %= m, m);
  assert(y == 1);
  return 1LL * x * (u + mod) % mod;
}
//! https://codeforces.com/blog/entry/127823
//! @code
//!   vi c = xor_conv(a, b);
//!   // must have sz(a) == sz(b) == a power of 2
//!   // c[k] = sum of a[i]*b[j] where i^j==k
//! @endcode
//! @time O(n log n)
//! @space O(n)
void fwht(int n, vector<int>& a) {
  for (int i = 1; i < n; i *= 2)
    for (int j = 0; j < n; j += 2 * i)
      for (int k = 0; k < i; k++) {
        int x = a[j + k], y = a[i + j + k];
        a[j + k] = (x + y) % mod;
        a[i + j + k] = (x - y + mod) % mod;
      }
}
vector<int> xor_conv(vector<int> a, vector<int> b) {
  int n = ssize(a), inv = mod_div(1, n);
  fwht(n, a);
  fwht(n, b);
  vector<int> res(n);
  for (int i = 0; i < n; i++) res[i] = 1LL * a[i] * b[i] % mod;
  fwht(n, res);
  for (int i = 0; i < n; i++) res[i] = 1LL * res[i] * inv % mod;
  return res;
}
