//! @code
//!   vector<basic_string<array<int, 2>>> g(n);
//!   vector<pair<int, int>> edges(m);
//!   for (int i = 0; i < m; i++) {
//!     int u, v;
//!     cin >> u >> v;
//!     u--, v--;
//!     g[u] += {v, i};
//!     edges[i] = {u, v};
//!   }
//!   vector<pair<int, int>> path =
//!     euler_path(g, m, source);
//! @endcode
//! @time O(n + m)
//! @space O(n + m)
vector<pair<int, int>> euler_path(auto& g, int m, int s) {
  vector<int> vis(m);
  vector<pair<int, int>> path;
  [&](this auto&& self, int u, int eu) -> void {
    while (!empty(g[u])) {
      auto [v, ev] = g[u].back();
      g[u].pop_back();
      if (!vis[ev]) vis[ev] = 1, self(v, ev);
    }
    path.emplace_back(u, eu);
  }(s, -1);
  ranges::reverse(path);
  return path;
}
