#define PROBLEM \
  "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"
#include "../../../kactl/content/number-theory/euclid.h"
// trick to remove const so I can use arbitrary prime mode
// here
#define const ;
#include "../../../library/math/mod_int_pow.hpp"
#undef const
int main() {
  cin.tie(0)->sync_with_stdio(0);
  mint val;
  assert(val.x == 0);
  vector<int> mods = {1, 4, 998'244'353, 1'000'000'007};
  for (int i = 0; i < 1'000'000; i++) {
    int type = rnd(0, 5);
    if (type == 0) {
      mod = mods[rnd(0, sz(mods) - 1)];
      val = rnd(-mod + 1, mod - 1);
      assert(0 <= val.x && val.x < mod);
    } else if (type == 1) {
      int to_add = rnd(-mod + 1, mod - 1);
      int prev_val = val.x;
      val = val + mint(to_add);
      assert(
        val.x == (1LL * prev_val + to_add + mod) % mod);
    } else if (type == 2) {
      int to_sub = rnd(-mod + 1, mod - 1);
      int prev_val = val.x;
      val = val - mint(to_sub);
      assert(
        val.x == (1LL * prev_val - to_sub + mod) % mod);
    } else if (type == 3) {
      int to_mult = rnd(-mod + 1, mod - 1);
      int prev_val = val.x;
      val = val * mint(to_mult);
      assert(
        val.x == (1LL * prev_val * (to_mult + mod)) % mod);
    } else if (type == 4) {
      if (mod == 1 || mod == 4) continue;
      int to_divide = rnd(1, mod - 1);
      int prev_val = val.x;
      val = val / mint(to_divide);
      assert(
        val.x == (mpow(to_divide, mod - 2) * prev_val).x);
    } else {
      assert(type == 5);
      int pow = rnd(0, 20);
      int prev_val = val.x;
      int naive = 1;
      for (int j = 0; j < pow; j++)
        naive = 1LL * naive * prev_val % mod;
      val = mpow(val, pow);
      assert(val.x == naive);
      if (mod == 1 && pow == 0) val.x %= mod;
    }
    assert(0 <= val.x && val.x < mod);
  }
  for (mod = 1; mod < 300; mod++) {
    for (int init = 0; init < mod; init++) {
      ll x, y;
      ll gcd = euclid(init, mod, x, y);
      assert(x * init + y * mod == gcd);
      assert(-mod / gcd < x && x < mod / gcd);
      if (gcd == 1)
        assert((mint(1) / init).x == mint(x).x);
    }
  }
  cout << "Hello World\n";
  return 0;
}
