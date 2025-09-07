#define PROBLEM \
  "https://judge.yosupo.jp/problem/system_of_linear_equations"
#include "../template.hpp"
#include "../../../library/math/matrix_related/solve_linear_mod.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, m;
  cin >> n >> m;
  vector<vector<int>> mat(n, vector<int>(m));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) cin >> mat[i][j];
  vector<int> b(n);
  for (int i = 0; i < n; i++) cin >> b[i];
  solve_linear_mod info(mat, b);
  assert(info.rank <= min(n, m));
  if (empty(info.sol)) {
    cout << -1 << '\n';
    return 0;
  }
  cout << m - info.rank << '\n';
  for (int val : info.sol) cout << val << " ";
  cout << '\n';
  vector<int> pivot(m, -1);
  for (int i = 0, j = 0; i < info.rank; i++) {
    while (mat[i][j] == 0) j++;
    pivot[j] = i;
  }
  for (int j = 0; j < m; j++)
    if (pivot[j] == -1) {
      vector<int> x(m, 0);
      x[j] = mod - 1;
      for (int k = 0; k < j; k++)
        if (pivot[k] != -1) x[k] = mat[pivot[k]][j];
      for (int k = 0; k < m; k++) cout << x[k] << " ";
      cout << '\n';
    }
  return 0;
}
