#pragma once
//! https://codeforces.com/blog/entry/125018
//! @code
//!   vector<basic_string<int>> adj(n);
//!   shallowest(adj, [&](int cent) {
//!   });
//! @endcode
//! @time O(n log n)
//! @space O(n)
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
  for (const auto& vec : order | views::reverse)
    for (int v : vec) {
      f(v);
      for (int u : adj[v])
        iter_swap(ranges::find(adj[u], v), rbegin(adj[u])),
          adj[u].pop_back();
    }
}
