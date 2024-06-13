#define PROBLEM \
  "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"

#include "../../../library/contest/random.hpp"
#include "../../../library/data_structures/dsu/dsu_restorable.hpp"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  for (int n = 1; n < 100; n++) {
    dsu_restorable dsu(n);
    vector<vector<int>> adj(n);
    vector<pair<int, int>> edge_st;
    for (int q = 0; q < 100; q++) {
      int type = get_rand<int>(0, 2);
      if (type == 0) {
        int u = get_rand<int>(0, n - 1), v = get_rand(0, n - 1);
        dsu.join(u, v);
        adj[u].push_back(v);
        adj[v].push_back(u);
        edge_st.emplace_back(u, v);
      } else if (type == 1) {
        vector<vector<int>> comps;
        vector<bool> vis(n);
        auto dfs = [&](auto&& self, int node) -> void {
          comps.back().push_back(node);
          for (auto next : adj[node])
            if (!vis[next]) {
              vis[next] = true;
              self(self, next);
            }
        };
        for (int i = 0; i < n; i++) {
          if (!vis[i]) {
            comps.emplace_back();
            vis[i] = true;
            dfs(dfs, i);
          }
        }
        assert(sz(comps) == dsu.num_sets);
        for (auto& cc : comps)
          for (auto node : cc) assert(dsu.size(node) == sz(cc));
      } else if (!empty(edge_st)) {
        auto [u, v] = edge_st.back();
        edge_st.pop_back();
        assert(adj[u].back() == v && adj[v].back() == u);
        adj[u].pop_back();
        adj[v].pop_back();
        dsu.undo();
      }
    }
  }
  cout << "Hello World\n";
  return 0;
}
