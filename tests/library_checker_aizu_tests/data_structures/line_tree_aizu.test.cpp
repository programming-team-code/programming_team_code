#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_12_A"
#include "../template.hpp"
#include "../../../library/data_structures/dsu/line_tree.hpp"
#include "../../../library/data_structures/rmq.hpp"
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
  auto [llist, uf] = line_tree(w_eds, n);
  rep(k, 0, n) rep(i, 0, n) rep(j, 0, n) {
    mat[i][j] = min(mat[i][j], max(mat[i][k], mat[k][j]));
  }
  int mst_sum = 0;
  vector<int> edge_weights;
  vector<int> to_time(n);
  for (int v = uf.find(0), timer = 1; llist[v].first != -1;
       v = llist[v].first, timer++) {
    edge_weights.push_back(llist[v].second);
    to_time[llist[v].first] = timer;
    mst_sum += llist[v].second;
  }
  RMQ rmq(edge_weights,
    [&](int x, int y) { return max(x, y); });
  rep(i, 0, n) rep(j, i + 1, n) {
    auto [i1, i2] = minmax(to_time[i], to_time[j]);
    assert(rmq.query(i1, i2) == mat[i][j]);
  }
  cout << mst_sum << '\n';
  return 0;
}
