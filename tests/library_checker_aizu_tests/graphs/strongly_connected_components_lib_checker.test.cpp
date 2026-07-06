#define PROBLEM "https://judge.yosupo.jp/problem/scc"
#include "../template.hpp"
#include "../../../library/graphs/strongly_connected_components/add_edges_strongly_connected.hpp"
#include "../scc_asserts.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, m;
  cin >> n >> m;
  vector<vi> adj(n);
  rep(i, 0, m) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
  }
  scc_asserts(adj);
  auto [num_sccs, scc_id] = scc(adj);
  cout << num_sccs << '\n';
  vector<vi> each_scc(num_sccs);
  rep(i, 0, n) each_scc[scc_id[i]].push_back(i);
  for (int i = num_sccs - 1; i >= 0; i--) {
    cout << sz(each_scc[i]) << " ";
    for (auto node : each_scc[i]) cout << node << " ";
    cout << '\n';
  }
  return 0;
}
