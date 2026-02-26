#pragma once
//! @code
//!   vector<basic_string<array<int, 2>>> adj(n);
//!   rep(i, 0, m) {
//!     int u, v;
//!     cin >> u >> v;
//!     u--, v--;
//!     adj[u] += {v, i};
//!   }
//!   vector<pii> path = euler_path(adj, m, s);
//! @endcode
//! @time O(n + m)
//! @space O(n + m)
vector<pii> euler_path(auto& adj, int m, int s) {
  vi vis(m);
  vector<pii> path;
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
