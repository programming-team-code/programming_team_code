#define PROBLEM \
  "https://judge.yosupo.jp/problem/minimum_spanning_tree"
#include "../template.hpp"
#include "../../../library/dsu/line_tree.hpp"
#include "../../../library/dsu/kruskal_tree.hpp"
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
  for (auto [i, u, v] : w_eds) lt.join(u, v);
  assert(lt.size(0) == n);
  int64_t cost = 0;
  vector<int> ids;
  for (int v = lt.find(0); lt.edge[v].first != -1;
    v = lt.edge[v].first) {
    ids.push_back(w_eds[lt.edge[v].second][0]);
    cost += weights[w_eds[lt.edge[v].second][0]];
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
