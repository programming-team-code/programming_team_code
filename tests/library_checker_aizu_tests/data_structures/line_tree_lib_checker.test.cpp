#define PROBLEM \
  "https://judge.yosupo.jp/problem/minimum_spanning_tree"
#include "../template.hpp"
#include "../../../library/data_structures/dsu/line_tree.hpp"
#include "../../../library/data_structures/dsu/kruskal_tree.hpp"
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
  line_tree lt(n);
  vector<int> idxs;
  for (auto [i, u, v] : w_eds)
    if (lt.join(u, v)) idxs.push_back(i);
  int64_t cost = 0;
  vector<int> ids;
  for (int v = lt.find(0); lt.t[v].edge.first != -1;
       v = lt.t[v].edge.first) {
    ids.push_back(idxs[lt.t[v].edge.second]);
    cost += weights[idxs[lt.t[v].edge.second]];
  }
  {
    kr_tree kt(n);
    int64_t kr_tree_cost = 0;
    for (auto [e_id, u, v] : w_eds)
      if (kt.join(u, v)) kr_tree_cost += weights[e_id];
    assert(kr_tree_cost == cost);
  }
  cout << cost << '\n';
  for (int id : ids) cout << id << ' ';
  cout << '\n';
  return 0;
}
