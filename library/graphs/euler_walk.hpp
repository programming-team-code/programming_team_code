#pragma once
vector<pii> euler_walk(auto& adj, int m, int s) {
  vi vis(m);
  vector<pii> path;
  auto dfs = [&](auto&& self, int u, int e) -> void {
    while (!empty(adj[u])) {
      auto [v, e_id] = adj[u].back();
      adj[u].pop_back();
      if (vis[e_id]) continue;
      vis[e_id] = 1;
      self(self, v, e_id);
    }
    path.push_back({u, e});
  };
  dfs(dfs, s, -1);
  ranges::reverse(path);
  return path;
}
