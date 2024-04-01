/** @file */
#pragma once
#include "../../../kactl/content/numerical/FastFourierTransform.h"
#include "edge_cd.hpp"
/**
 * @param adj unrooted, connected tree
 * @returns array `num_paths` where `num_paths[i]` = # of paths in tree with `i`
 * edges. `num_paths[1]` = # edges
 * @time O(n * log1.5(n) * log2(n))
 * @space this function allocates/returns various vectors which are each O(n)
 */
vector<ll> count_paths_per_length(const vector<vector<int>>& adj) {
  vector<ll> num_paths(sz(adj));
  num_paths[1] = sz(adj) - 1;
  edge_cd(adj, [&](const vector<vector<int>>& cd_adj, int cent, int split) {
    vector<vector<double>> cnt(2, vector<double>(1));
    auto dfs = [&](auto&& self, int u, int p, int d, int side) -> void {
      if (sz(cnt[side]) == d) cnt[side].push_back(0.0);
      cnt[side][d]++;
      for (int v : cd_adj[u])
        if (v != p) self(self, v, u, 1 + d, side);
    };
    for (int i = 0; i < sz(cd_adj[cent]); i++)
      dfs(dfs, cd_adj[cent][i], cent, 1, i < split);
    vector<double> prod = conv(cnt[0], cnt[1]);
    for (int i = 0; i < sz(prod); i++)
      num_paths[i] += llround(prod[i]);
  });
  return num_paths;
}
