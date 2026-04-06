#pragma once
//! https://codeforces.com/blog/entry/125018
//! @code
//!   vector<basic_string<int>> g(n);
//!   shallowest(g, [&](int cent) {
//!   });
//! @endcode
//! @time O(n log n)
//! @space O(n)
void shallowest(auto& g, auto f) {
  vector<vi> order(bit_width(size(g)));
  auto dfs = [&](auto&& self, int u, int p) -> int {
    int once = 0, twice = 0;
    for (int v : g[u])
      if (v != p) {
        int dp = self(self, v, u);
        twice |= once & dp, once |= dp;
      }
    auto dp = (once | (bit_ceil(twice + 1u) - 1)) + 1;
    order[countr_zero(dp)].push_back(u);
    return dp;
  };
  dfs(dfs, 0, 0);
  for (const vi& vec : order | views::reverse)
    for (int u : vec) {
      f(u);
      for (int v : g[u])
        iter_swap(ranges::find(g[v], u), rbegin(g[v])),
          g[v].pop_back();
    }
}
