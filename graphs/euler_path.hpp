//! @code
//!   vector<basic_string<array<int, 2>>> g(n);
//!   vector<pii> edges(m);
//!   rep(i, 0, m) {
//!     int u, v;
//!     cin >> u >> v;
//!     u--, v--;
//!     g[u] += {v, i};
//!     edges[i] = {u, v};
//!   }
//!   vector<pii> path = euler_path(g, m, source);
//! @endcode
//! @time O(n + m)
//! @space O(n + m)
vector<pair<int, int>> euler_path(auto& g, int m, int s) {
  vector<int> vis(m);
  vector<pair<int, int>> path;
  auto dfs = [&](auto dfs, int u, int eu) -> void {
    while (!empty(g[u])) {
      auto [v, ev] = g[u].back();
      g[u].pop_back();
      if (!vis[ev]) vis[ev] = 1, dfs(dfs, v, ev);
    }
    path.emplace_back(u, eu);
  };
  dfs(dfs, s, -1);
  ranges::reverse(path);
  return path;
}
