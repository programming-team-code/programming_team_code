#define PROBLEM                      \
  "https://judge.yosupo.jp/problem/" \
  "system_of_linear_equations"
#include "../template.hpp"

#include "../../../library/math/matrix_related/solve_linear_mod.hpp"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, m;
  cin >> n >> m;
  vector<vector<mint>> mat(n, vector<mint>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) cin >> mat[i][j].x;
  }
  vector<mint> b(n);
  for (int i = 0; i < n; i++) cin >> b[i].x;
  solve_linear_mod info(mat, b);
  assert(info.rank <= min(n, m));
  if (empty(info.x)) {
    cout << -1 << '\n';
    return 0;
  }
  cout << m - info.rank << '\n';
  for (auto val : info.x) cout << val.x << " ";
  cout << '\n';
  vector<int> pivot(m, -1);
  for (int i = 0, j = 0; i < info.rank; i++) {
    while (mat[i][j].x == 0) j++;
    pivot[j] = i;
  }
  for (int j = 0; j < m; j++)
    if (pivot[j] == -1) {
      vector<mint> x(m, 0);
      x[j] = -1;
      assert(0 <= x[j].x && x[j].x < mod);
      for (int k = 0; k < j; k++)
        if (pivot[k] != -1) x[k] = mat[pivot[k]][j];
      for (int k = 0; k < m; k++)
        cout << x[k].x << " ";
      cout << '\n';
    }
  return 0;
}
