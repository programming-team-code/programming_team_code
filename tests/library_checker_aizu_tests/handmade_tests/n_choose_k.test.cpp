#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"

#define mod mod_1
#include "../../../library/math/n_choose_k/large_n_choose_small_k.hpp"
#undef mod
#include "../../../library/math/n_choose_k/lucas_theorem.hpp"

int main() {
  cin.tie(0)->sync_with_stdio(0);
#define mod mod_2
#include "../../../library/math/n_choose_k/pascals_identity.hpp"
#undef mod
  for (int i = 0; i < mx; i++) {
    assert(choose[i][0] == 1 && end(choose[i])[-1] == 1);
    assert(lucas(i, -1) == 0);
    assert(c_small_k(i, -1) == 0);
    assert(lucas(i, i + 1) == 0);
    assert(c_small_k(i, i + 1) == 0);
    assert(lucas(-1, i) == 0);
    assert(c_small_k(-1, i) == 0);
    assert(lucas(i, i - 1) == i % mod);
    if (i - 1 < mod)
      assert(c_small_k(i, i - 1) == i % mod);
    for (int j = 0; j < sz(choose[i]); j++) {
      assert(lucas(i, j) == choose[i][j]);
      if (j < mod)
        assert(c_small_k(i, j) == choose[i][j]);
    }
  }
  for (int tests = 100'000; tests--;) {
    auto n = get_rand<int64_t>(-1e18, 1e18);
    auto k = get_rand<int>(-mod, mod - 1);
    assert(lucas(n, k) == c_small_k(n, k));
  }
  assert(lucas(371283LL, 32981LL) == 0);
  assert(lucas(47382946300290018LL, 47382946300290014LL) == 7);
  assert(lucas(4032010405302301LL, 403201040302301LL) == 0);
  assert(lucas(4032010405302301LL, 4032010405302298LL) == 4);
  cout << "Hello World\n";
  return 0;
}
