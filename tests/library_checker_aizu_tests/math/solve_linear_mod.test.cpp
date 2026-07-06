#define PROBLEM \
  "https://judge.yosupo.jp/problem/system_of_linear_equations"
#include "../template.hpp"
#include "../../../library/math/matrix_related/solve_linear_mod.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, m;
  cin >> n >> m;
  vector<vi> mat(n, vi(m));
  rep(i, 0, n) rep(j, 0, m) cin >> mat[i][j];
  vi b(n);
  rep(i, 0, n) cin >> b[i];
  solve_linear_mod info(mat, b);
  assert(info.rank <= min(n, m));
  if (empty(info.sol)) {
    cout << -1 << '\n';
    return 0;
  }
  cout << m - info.rank << '\n';
  for (int val : info.sol) cout << val << " ";
  cout << '\n';
  vi pivot(m, -1);
  for (int i = 0, j = 0; i < info.rank; i++) {
    while (mat[i][j] == 0) j++;
    pivot[j] = i;
  }
  rep(j, 0, m) if (pivot[j] == -1) {
    vi x(m, 0);
    x[j] = mod - 1;
    rep(k, 0, j) if (pivot[k] != -1)
      x[k] = mat[pivot[k]][j];
    rep(k, 0, m) cout << x[k] << " ";
    cout << '\n';
  }
  return 0;
}
