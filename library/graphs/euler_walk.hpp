#pragma once
vector<pii> euler_walk(auto& adj, int m, int s) {
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
