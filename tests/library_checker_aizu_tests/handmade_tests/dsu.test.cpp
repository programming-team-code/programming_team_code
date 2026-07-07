#define PROBLEM \
  "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"
#include "../../../library/dsu/dsu.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  for (int n = 0; n <= 100; n++) {
    vector<vi> adj(n);
    DSU dsu(n);
    rep(q, 0, n) {
      int u = rnd(0, n - 1);
      int v = rnd(0, n - 1);
      bool joined = dsu.join(u, v);
      {
        vector<bool> vis(n);
        auto dfs = [&](this auto&& self, int v) -> void {
          for (int u : adj[v]) {
            if (!vis[u]) {
              vis[u] = 1;
              self(u);
            }
          }
        };
        vis[u] = 1;
        dfs(u);
        assert(vis[v] != joined);
      }
      adj[u].push_back(v);
      adj[v].push_back(u);
      rep(i, 0, n) {
        vector<bool> vis(n);
        int cnt_nodes = 0;
        auto dfs = [&](this auto&& self, int v) -> void {
          cnt_nodes++;
          for (int u : adj[v]) {
            if (!vis[u]) {
              vis[u] = 1;
              self(u);
            }
          }
        };
        vis[i] = 1;
        dfs(i);
        assert(cnt_nodes == dsu.size(i));
      }
    }
  }
  cout << "Hello World\n";
  return 0;
}
