#pragma once
//! @code
//!   vector<basic_string<int>> adj(n);
//!   centroid(adj, [&](int cent, int par_cent) {});
//! @endcode
//! @time O(n log n)
//! @space O(n)
void centroid(auto& adj, auto f) {
  vi siz(sz(adj));
  auto dfs_sz = [&](auto&& dfs_sz, int u, int p) -> void {
    siz[u] = 1;
    for (int v : adj[u])
      if (v != p) dfs_sz(dfs_sz, v, u), siz[u] += siz[v];
  };
  auto dfs = [&](auto&& dfs, int u, int p) -> void {
    dfs_sz(dfs_sz, u, -1);
    for (int w = -1, sz_root = siz[u];;) {
      auto big_ch = ranges::find_if(adj[u], [&](int v) {
        return v != w && 2 * siz[v] > sz_root;
      });
      if (big_ch == end(adj[u])) break;
      w = u, u = *big_ch;
    }
    f(u, p);
    for (int v : adj[u]) {
      iter_swap(ranges::find(adj[v], u), rbegin(adj[v]));
      adj[v].pop_back();
      dfs(dfs, v, u);
    }
  };
  dfs(dfs, 0, -1);
}
