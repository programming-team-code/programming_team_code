#define PROBLEM                      \
  "https://judge.yosupo.jp/problem/" \
  "cycle_detection"
#include "../template.hpp"
#include "../scc_asserts.hpp"

#include "../../../library/graphs/strongly_connected_components/add_edges_strongly_connected.hpp"

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
  sccs scc(adj);
  vector<int> color(n);
  vector<pair<int /*edge id*/,
    int /*node closer to root*/>>
    edge_stack;
  auto dfs = [&](auto&& self, int u) -> void {
    for (auto [v, e_id] : adj_edge_id[u]) {
      if (color[v] == 0) {
        color[v] = 1;
        edge_stack.emplace_back(e_id, u);
        self(self, v);
        edge_stack.pop_back();
        color[v] = 2;
      } else if (color[v] == 1) {
        vector<int> res(1, e_id);
        while (1) {
          auto [curr_edge_id, curr_node] =
            edge_stack.back();
          edge_stack.pop_back();
          assert(
            scc.scc_id[curr_node] == scc.scc_id[u]);
          res.push_back(curr_edge_id);
          if (curr_node == v) break;
        }
        cout << sz(res) << '\n';
        for (int i = sz(res) - 1; i >= 0; i--)
          cout << res[i] << '\n';
        exit(0);
      }
    }
  };
  for (int i = 0; i < n; i++) {
    if (color[i] == 0) {
      color[i] = 1;
      dfs(dfs, i);
      color[i] = 2;
    }
  }
  assert(scc.num_sccs == n);
  cout << -1 << '\n';
  return 0;
}
