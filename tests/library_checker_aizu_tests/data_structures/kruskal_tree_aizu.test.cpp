#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_12_A"
#include "../template.hpp"
#include "../../../library/dsu/kruskal_tree.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n;
  cin >> n;
  vector<array<int, 3>> w_eds;
  vector<vector<int>> mat(n, vector<int>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> mat[i][j];
      if (mat[i][j] == -1) {
        mat[i][j] = INT_MAX;
        continue;
      }
      w_eds.push_back({mat[i][j], i, j});
    }
  }
  sort(all(w_eds));
  kr_tree kt(n);
  vector<int> weight(2 * n);
  for (auto [w, u, v] : w_eds)
    if (kt.join(u, v)) weight[kt.id - 1] = w;
  rep(k, 0, n) rep(i, 0, n) rep(j, 0, n) {
    mat[i][j] = min(mat[i][j], max(mat[i][k], mat[k][j]));
  }
  int mst_sum = 0;
  for (int i = n; i < kt.id; i++) mst_sum += weight[i];
  vector<int> depth(2 * n);
  vector<int> actual_par(2 * n, -1);
  auto dfs = [&](auto&& self, int v) -> void {
    for (int u : kt.adj[v]) {
      depth[u] = 1 + depth[v];
      actual_par[u] = v;
      self(self, u);
    }
  };
  dfs(dfs, kt.id - 1);
  rep(i, 0, n) rep(j, i + 1, n) {
    int u = i, v = j;
    while (u != v)
      if (depth[u] > depth[v]) u = actual_par[u];
      else v = actual_par[v];
    assert(weight[u] == mat[i][j]);
  }
  cout << mst_sum << '\n';
  return 0;
}
