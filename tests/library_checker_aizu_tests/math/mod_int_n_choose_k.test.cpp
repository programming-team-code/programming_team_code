#define PROBLEM \
  "https://judge.yosupo.jp/problem/binomial_coefficient_prime_mod"
#include "../template.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int t, mod;
  cin >> t >> mod;
  const int mx_n = min(int(1e7), mod);
  vector<int> fact(mx_n, 1);
  for (int i = 2; i < mx_n; i++) fact[i] = fact[i - 1] * i;
  vector<mint> inv_fact(mx_n, 1);
  inv_fact.back() = mint(1) / fact.back();
  for (int i = mx_n - 2; i >= 1; i--)
    inv_fact[i] = inv_fact[i + 1] * (i + 1);
  for (int i = 0; i < mx_n; i++) {
    assert((fact[i] * inv_fact[i]).x == 1);
    assert(inv_fact[i].x == (mint(1) / fact[i]).x);
  }
  while (t--) {
    int n, k;
    cin >> n >> k;
    if (k < 0 || k > n) cout << 0 << '\n';
    else
      cout << (fact[n] * inv_fact[k] * inv_fact[n - k]).x
           << '\n';
  }
  return 0;
}
