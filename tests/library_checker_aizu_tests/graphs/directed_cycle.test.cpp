#define PROBLEM \
  "https://judge.yosupo.jp/problem/cycle_detection"
#include "../template.hpp"
#include "../scc_asserts.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, m;
  cin >> n >> m;
  vector<vector<int>> adj(n);
  vector<vector<pair<int, int>>> adj_edge_id(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj_edge_id[u].emplace_back(v, i);
  }
  scc_asserts(adj);
  auto [num_sccs, scc_id] = sccs(adj);
  if (num_sccs == n) {
    cout << -1 << '\n';
    return 0;
  }
  vi scc_siz(num_sccs);
  vi any_node(num_sccs);
  rep(i, 0, n) {
    any_node[scc_id[i]] = i;
    scc_siz[scc_id[i]]++;
  }
  rep(i, 0, num_sccs) {
    if (scc_siz[i] > 1) {
      int v = any_node[i];
      vi vis(n);
      while (!vis[v]) {
        vis[v] = 1;
        for (auto [next, _] : adj_edge_id[v]) {
          if (scc_id[v] == scc_id[next]) {
            v = next;
            break;
          }
        }
      }
      vi cycle;
      while (vis[v] == 1) {
        vis[v] = 2;
        for (auto [next, e_id] : adj_edge_id[v]) {
          if (scc_id[v] == scc_id[next]) {
            cycle.push_back(e_id);
            v = next;
            break;
          }
        }
      }
      cout << sz(cycle) << '\n';
      for (int node : cycle) cout << node << '\n';
      return 0;
    }
  }
  assert(0);
  return 0;
}
