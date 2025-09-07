#pragma once
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
