#define PROBLEM \
  "https://judge.yosupo.jp/problem/minimum_spanning_tree"
#include "../template.hpp"
#include "../../../library/data_structures/dsu/line_tree.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, m;
  cin >> n >> m;
  vector<array<int, 3>> w_eds(m);
  vector<int> weights(m);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v >> weights[i];
    w_eds[i] = {i, u, v};
  }
  sort(all(w_eds),
       [&](const array<int, 3>& x, const array<int, 3>& y)
           -> bool { return weights[x[0]] < weights[y[0]]; });
  auto [llist, uf] = line_tree(w_eds, n);
  int64_t cost = 0;
  vector<int> ids;
  for (int v = uf.find(0); llist[v].first != -1;
       v = llist[v].first) {
    ids.push_back(llist[v].second);
    cost += weights[llist[v].second];
  }
  cout << cost << '\n';
  for (int id : ids) cout << id << ' ';
  cout << '\n';
  return 0;
}
