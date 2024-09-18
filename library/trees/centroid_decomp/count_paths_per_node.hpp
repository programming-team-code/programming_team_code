#pragma once
#include "centroid_decomp.hpp"
//! @param adj unrooted, connected forest
//! @param k number of edges
//! @returns array `num_paths` where `num_paths[i]` = number
//! of paths with k edges where node `i` is on the path.
//! 0-based nodes.
//! @time O(n log n)
//! @space this function allocates/returns various vectors
//! which are all O(n)
vector<ll> count_paths_per_node(const vector<vi>& adj,
  int k) {
  vector<ll> num_paths(sz(adj));
  centroid(adj, [&](const vector<vi>& cd_adj, int cent) {
    vector pre_d{1}, cur_d{0};
    auto dfs = [&](auto&& self, int v, int p, int d) -> ll {
      if (d > k) return 0LL;
      if (sz(cur_d) <= d) cur_d.push_back(0);
      cur_d[d]++;
      ll cnt = 0;
      if (k - d < sz(pre_d)) cnt += pre_d[k - d];
      for (int u : cd_adj[v])
        if (u != p) cnt += self(self, u, v, d + 1);
      num_paths[v] += cnt;
      return cnt;
    };
    auto dfs_child = [&](int child) -> ll {
      ll cnt = dfs(dfs, child, cent, 1);
      pre_d.resize(sz(cur_d));
      for (int i = 1; i < sz(cur_d) && cur_d[i]; i++)
        pre_d[i] += cur_d[i], cur_d[i] = 0;
      return cnt;
    };
    for (int child : cd_adj[cent])
      num_paths[cent] += dfs_child(child);
    pre_d = cur_d = {0};
    for_each(rbegin(cd_adj[cent]), rend(cd_adj[cent]),
      dfs_child);
  });
  return num_paths;
}
