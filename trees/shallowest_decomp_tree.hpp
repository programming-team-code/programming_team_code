//! https://codeforces.com/blog/entry/125018
//! @code
//!   vector<basic_string<int>> adj(n);
//!   shallowest(adj, [&](int cent) {
//!   });
//! @endcode
//! @time O(n log n)
//! @space O(n)
void shallowest(auto& adj, auto f) {
  vector<vector<int>> order(bit_width(size(adj)));
  auto dfs = [&](auto&& self, int u, int p) -> int {
    int once = 0, twice = 0;
    for (int v : adj[u])
      if (v != p) {
        int dp = self(self, v, u);
        twice |= once & dp, once |= dp;
      }
    auto dp = (once | (bit_ceil(twice + 1u) - 1)) + 1;
    order[countr_zero(dp)].push_back(u);
    return dp;
  };
  dfs(dfs, 0, 0);
  for (const vector<int>& vec : order | views::reverse)
    for (int u : vec) {
      f(u);
      for (int v : adj[u])
        iter_swap(ranges::find(adj[v], u), rbegin(adj[v])),
          adj[v].pop_back();
    }
}
