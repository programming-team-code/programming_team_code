#define PROBLEM \
  "https://judge.yosupo.jp/problem/connected_components_of_complement_graph"
#include "../template.hpp"
#include "../../../library/graphs/uncommon/complement_graph_ccs.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, m;
  cin >> n >> m;
  vector<vector<int>> adj(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  auto cc_id = get_complement_graph_ccs(adj);
  int num_ccs = *max_element(begin(cc_id), end(cc_id)) + 1;
  vector<vector<int>> ccs(num_ccs);
  for (int u = 0; u < n; u++) ccs[cc_id[u]].push_back(u);
  cout << num_ccs << '\n';
  for (auto& cc : ccs) {
    cout << size(cc);
    for (int v : cc) cout << ' ' << v;
    cout << '\n';
  }
  return 0;
}
