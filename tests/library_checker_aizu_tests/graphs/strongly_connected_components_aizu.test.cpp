#define PROBLEM \
  "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_C"
#include "../../../library/graphs/strongly_connected_components/add_edges_strongly_connected.hpp"
#include "../scc_asserts.hpp"
#include "../template.hpp"
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
  int q;
  cin >> q;
  while (q--) {
    int u, v;
    cin >> u >> v;
    cout << (scc_id[u] == scc_id[v]) << '\n';
  }
  return 0;
}
