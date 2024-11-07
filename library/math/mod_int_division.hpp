#pragma once
mint operator/(mint b) {
  int m = mod, u = 1, v = 0;
  while (m)
    u = exchange(v, u - b.x / m * v),
    b.x = exchange(m, b.x % m);
  assert(b.x == 1);
  return *this * u;
}
