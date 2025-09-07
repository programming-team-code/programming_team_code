#define PROBLEM \
  "https://judge.yosupo.jp/problem/matrix_det"
#include "../template.hpp"
#include "../../../library/math/matrix_related/row_reduce.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n;
  cin >> n;
  vector<vector<int>> matrix(n, vector<int>(n));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) cin >> matrix[i][j];
  auto [rank, det] = row_reduce(matrix, n);
  cout << det << '\n';
  return 0;
}
