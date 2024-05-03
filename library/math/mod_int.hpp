/** @file */
#pragma once
const int mod = 998244353;
/**
 * @see https://github.com/kth-competitive-programming/kactl /blob/main/content/number-theory/ModularArithmetic.h
 * @see https://codeforces.com/blog/entry/122714
 */
struct mint {
  int x;
  mint(int xx = 0) : x(xx < 0 ? xx + mod : xx) {}
  mint operator+(mint b) { return x - mod + b.x; }
  mint operator-(mint b) { return x - b.x; }
  mint operator*(mint b) { return ll(x) * b.x % mod; }
  mint operator/(mint b) {
    int m = mod, u = 1, v = 0;
    while (m) u = exchange(v, u - b.x / m * v), b.x = exchange(m, b.x % m);
    assert(b.x == 1);
    return *this * u;
  }
  mint operator^(ll e) {
    assert(e >= 0);
    mint res = 1, r = x;
    for (; e; e /= 2, r = r * r)
      if (e & 1) res = res * r;
    return res;
  }
};
