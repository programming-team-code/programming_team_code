#define PROBLEM \
  "https://judge.yosupo.jp/problem/shortest_path"
// since this causes an O(n) heap-property check for each call to
//`priority_queue::push`, causing TLE.
#undef _GLIBCXX_DEBUG
#include "../template.hpp"
#include "../../../library/graphs/dijkstra.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, m, s, t;
  cin >> n >> m >> s >> t;
  vector<vector<pair<int, ll>>> adj(n), adj_inv(n);
  for (int i = 0; i < m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    adj[u].emplace_back(v, w);
    adj_inv[v].emplace_back(u, w);
  }
  vector<ll> len = dijkstra(adj, s);
  if (len[t] == LLONG_MAX) {
    cout << -1 << '\n';
    return 0;
  }
  assert(len[s] == 0);
  vector<bool> vis(n);
  vis[t] = 1;
  vector<array<int, 2>> path;
  auto dfs = [&](auto&& self, int u) -> bool {
    if (u == s) return 1;
    for (auto [v, w] : adj_inv[u]) {
      if (!vis[v] && len[v] != LLONG_MAX &&
        len[v] + w == len[u]) {
        vis[v] = 1;
        if (self(self, v)) {
          path.push_back({v, u});
          return 1;
        }
      }
    }
    return 0;
  };
  assert(dfs(dfs, t));
  cout << len[t] << " " << sz(path) << '\n';
  for (auto [u, v] : path) cout << u << " " << v << '\n';
  return 0;
}
