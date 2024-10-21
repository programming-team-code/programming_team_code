const int mod = 998244353;
//! https://github.com/kth-competitive-programming/kactl/blob/main/content/number-theory/ModularArithmetic.h
//! https://codeforces.com/blog/entry/122714
struct mint {
  int x;
  mint(int xx = 0): x(xx < 0 ? xx + mod : xx) {}
  mint operator+(mint b) { return x - mod + b.x; }
  mint operator-(mint b) { return x - b.x; }
  mint operator*(mint b) { return int64_t(x) * b.x % mod; }
  mint operator/(mint b) {
    int m = mod, u = 1, v = 0;
    while (m)
      u = exchange(v, u - b.x / m * v),
      b.x = exchange(m, b.x % m);
    assert(b.x == 1);
    return *this * u;
  }
};
//! https://github.com/kth-competitive-programming/kactl/blob/main/content/number-theory/ModPow.h
//! returns (b^e)%mod, 1 for 0^0.
//! @time O(log e)
//! @space O(1)
mint mpow(mint b, int64_t e) {
  mint res = 1;
  for (; e; e /= 2, b = b * b)
    if (e & 1) res = res * b;
  return res;
}
