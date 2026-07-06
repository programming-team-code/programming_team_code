#define PROBLEM \
  "https://judge.yosupo.jp/problem/matrix_product_mod_2"
#include "../template.hpp"
#include "../../../library/math/matrix_related/binary_matrix_mult.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, m, k;
  cin >> n >> m >> k;
  const int mx_n = 1 << 12;
  array<bitset<mx_n>, mx_n> m1, m2;
  rep(i, 0, n) {
    string row;
    cin >> row;
    rep(j, 0, m) m1[i][j] = row[j] - '0';
  }
  rep(i, 0, m) {
    string row;
    cin >> row;
    rep(j, 0, k) m2[i][j] = row[j] - '0';
  }
  auto prod = m1 * m2;
  rep(i, 0, n) {
    rep(j, 0, k) cout << prod[i][j];
    cout << '\n';
  }
  return 0;
}
