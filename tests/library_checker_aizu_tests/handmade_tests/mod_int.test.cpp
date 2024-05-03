#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"

#include "../../../library/contest/random.hpp"

#include "../../../library/math/mod_int_pow.hpp"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  mint val;
  assert(val.x == 0);
  for (int i = 0; i < 1'000'000; i++) {
    int type = get_rand(0, 5);
    if (type == 0) {
      val = get_rand(-mod + 1, mod - 1);
      assert(0 <= val.x && val.x < mod);
    } else if (type == 1) {
      int to_add = get_rand(-mod + 1, mod - 1);
      int prev_val = val.x;
      val = val + mint(to_add);
      assert(val.x == (1LL * prev_val + to_add + mod) % mod);
    } else if (type == 2) {
      int to_sub = get_rand(-mod + 1, mod - 1);
      int prev_val = val.x;
      val = val - mint(to_sub);
      assert(val.x == (1LL * prev_val - to_sub + mod) % mod);
    } else if (type == 3) {
      int to_mult = get_rand(-mod + 1, mod - 1);
      int prev_val = val.x;
      val = val * mint(to_mult);
      assert(val.x == (1LL * prev_val * (to_mult + mod)) % mod);
    } else if (type == 4) {
      int to_divide = get_rand(1, mod - 1);
      int prev_val = val.x;
      val = val / mint(to_divide);
      assert(val.x == (mpow(to_divide, mod - 2) * prev_val).x);
    } else {
      assert(type == 5);
      int pow = get_rand(0, 20);
      int prev_val = val.x;
      int naive = 1;
      for (int j = 0; j < pow; j++)
        naive = 1LL * naive * prev_val % mod;
      val = mpow(val, pow);
      assert(val.x == naive);
    }
    assert(0 <= val.x && val.x < mod);
  }
  cout << "Hello World\n";
  return 0;
}
