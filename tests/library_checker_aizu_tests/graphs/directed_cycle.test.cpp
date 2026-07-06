#define PROBLEM \
  "https://judge.yosupo.jp/problem/cycle_detection"
#include "../template.hpp"
#include "../scc_asserts.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, m;
  cin >> n >> m;
  vector<vi> adj(n);
  vector<vector<pii>> adj_edge_id(n);
  rep(i, 0, m) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj_edge_id[u].emplace_back(v, i);
  }
  scc_asserts(adj);
  auto [num_sccs, scc_id] = scc(adj);
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
        for (auto [nxt, _] : adj_edge_id[v]) {
          if (scc_id[v] == scc_id[nxt]) {
            v = nxt;
            break;
          }
        }
      }
      vi cycle;
      while (vis[v] == 1) {
        vis[v] = 2;
        for (auto [nxt, e_id] : adj_edge_id[v]) {
          if (scc_id[v] == scc_id[nxt]) {
            cycle.push_back(e_id);
            v = nxt;
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
