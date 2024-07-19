#define PROBLEM "https://judge.yosupo.jp/problem/binomial_coefficient_prime_mod"
#include "../template.hpp"

// trick to remove const so I can use arbitrary prime mode here
#define const ;
#include "../../../library/math/n_choose_k/n_choose_k.hpp"
#undef const

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int num_tests;
  cin >> num_tests >> mod;
  while (num_tests--) {
    int n, k;
    cin >> n >> k;
    cout << C(n, k) << '\n';
    if (n > 0) {
      assert(C(-n, k) == 0);
      assert(C(-n, -k) == 0);
      assert(C(k, -n) == 0);
      assert(C(-k, -n) == 0);
    }
    if (k > 0) {
      assert(C(n, -k) == 0);
      assert(C(-k, n) == 0);
    }
  }
  for (int i = 0; i < sz(t); i++) {
    if (i) assert(i * t[i].inv % mod == 1);
    assert(t[i].fact * t[i].inv_fact % mod == 1);
  }
  return 0;
}
