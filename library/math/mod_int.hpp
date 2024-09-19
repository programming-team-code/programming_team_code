#pragma once
const int mod = 998244353;
//! https://github.com/kth-competitive-programming/kactl/blob/main/content/number-theory/ModularArithmetic.h
//! https://codeforces.com/blog/entry/122714
struct mint {
  int x;
  mint(int xx = 0): x(xx < 0 ? xx + mod : xx) {}
  mint operator+(mint b) { return x - mod + b.x; }
  mint operator-(mint b) { return x - b.x; }
  mint operator*(mint b) { return ll(x) * b.x % mod; }
  mint operator/(mint b) {
    int m = mod, u = 1, v = 0;
    while (m)
      u = exchange(v, u - b.x / m * v),
      b.x = exchange(m, b.x % m);
    assert(b.x == 1);
    return *this * u;
  }
};
