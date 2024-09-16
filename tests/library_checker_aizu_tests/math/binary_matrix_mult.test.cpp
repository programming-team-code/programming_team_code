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
  for (int i = 0; i < n; i++) {
    string row;
    cin >> row;
    for (int j = 0; j < m; j++) m1[i][j] = row[j] - '0';
  }
  for (int i = 0; i < m; i++) {
    string row;
    cin >> row;
    for (int j = 0; j < k; j++) m2[i][j] = row[j] - '0';
  }
  auto prod = m1 * m2;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < k; j++) cout << prod[i][j];
    cout << '\n';
  }
  return 0;
}
