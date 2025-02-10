#define PROBLEM "https://judge.yosupo.jp/problem/scc"
#include "../template.hpp"
#include "../../../library/graphs/strongly_connected_components/add_edges_strongly_connected.hpp"
#include "../scc_asserts.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, m;
  cin >> n >> m;
  vector<vector<int>> adj(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
  }
  scc_asserts(adj);
  auto [num_sccs, scc_id] = sccs(adj);
  cout << num_sccs << '\n';
  vector<vector<int>> each_scc(num_sccs);
  for (int i = 0; i < n; i++)
    each_scc[scc_id[i]].push_back(i);
  for (int i = num_sccs - 1; i >= 0; i--) {
    cout << sz(each_scc[i]) << " ";
    for (auto node : each_scc[i]) cout << node << " ";
    cout << '\n';
  }
  return 0;
}
