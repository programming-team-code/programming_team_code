#pragma once
const int mod = 998244353;
int mod_div(int x, int y) {
  int m = mod, u = 1, v = 0;
  while (m) swap(u -= y / m * v, v), swap(y %= m, m);
  assert(y == 1);
  return 1LL * x * (u + mod) % mod;
}
