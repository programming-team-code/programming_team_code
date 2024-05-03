#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det"
#include "../template.hpp"

#include "../../../library/math/matrix_related/row_reduce.hpp"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n;
  cin >> n;
  vector<vector<mint>> matrix(n, vector<mint>(n));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      cin >> matrix[i][j].x;
  auto [rank, det] = row_reduce(matrix, n);
  cout << det.x << '\n';
  return 0;
}
