#define PROBLEM \
  "https://judge.yosupo.jp/problem/montmort_number_mod"
#include "../template.hpp"

#include "../../../library/math/derangements.hpp"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, mod;
  cin >> n >> mod;
  vector<ll> der = derangements(n + 1, mod);
  for (int i = 1; i <= n; i++) cout << der[i] << " ";
  cout << '\n';
  return 0;
}
