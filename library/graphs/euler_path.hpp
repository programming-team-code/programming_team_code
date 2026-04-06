#pragma once
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
vector<pii> euler_path(auto& g, int m, int s) {
  vi vis(m);
  vector<pii> path;
  auto dfs = [&](auto&& self, int u, int eu) -> void {
    while (!empty(g[u])) {
      auto [v, ev] = g[u].back();
      g[u].pop_back();
      if (!vis[ev]) vis[ev] = 1, self(self, v, ev);
    }
    path.emplace_back(u, eu);
  };
  dfs(dfs, s, -1);
  ranges::reverse(path);
  return path;
}
