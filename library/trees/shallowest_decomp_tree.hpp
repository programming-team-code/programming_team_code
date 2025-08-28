#pragma once
void shallowest(auto& adj, auto f) {
  vector<vi> order(bit_width(size(adj)));
  auto dfs = [&](auto&& self, int v, int p) -> int {
    int once = 0, twice = 0;
    for (int u : adj[v])
      if (u != p) {
        int dp = self(self, u, v);
        twice |= once & dp, once |= dp;
      }
    auto dp = (once | (bit_ceil(twice + 1u) - 1)) + 1;
    order[countr_zero(dp)].push_back(v);
    return dp;
  };
  dfs(dfs, 0, 0);
  for (auto& vec : order | views::reverse)
    for (int cent : vec) {
      f(cent);
      for (int v : adj[cent]) {
        iter_swap(ranges::find(adj[v], cent),
          rbegin(adj[v]));
        adj[v].pop_back();
      }
    }
}
