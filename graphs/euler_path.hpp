//! @code
//!   vector<basic_string<array<int, 2>>> adj(n);
//!   vector<pii> edges(m);
//!   rep(i, 0, m) {
//!     int u, v;
//!     cin >> u >> v;
//!     u--, v--;
//!     adj[u] += {v, i};
//!     edges[i] = {u, v};
//!   }
//!   vector<pii> path = euler_path(adj, m, source);
//! @endcode
//! @time O(n + m)
//! @space O(n + m)
vector<pair<int, int>> euler_path(auto& adj, int m,
  int s) {
  vector<int> vis(m);
  vector<pair<int, int>> path;
  auto dfs = [&](auto&& self, int u, int eu) -> void {
    while (!empty(adj[u])) {
      auto [v, ev] = adj[u].back();
      adj[u].pop_back();
      if (!vis[ev]) vis[ev] = 1, self(self, v, ev);
    }
    path.emplace_back(u, eu);
  };
  dfs(dfs, s, -1);
  ranges::reverse(path);
  return path;
}
