#pragma once
#include "../../../kactl/content/numerical/FastFourierTransform.h"
#include "../edge_cd.hpp"
//! @param adj unrooted, connected tree
//! @returns array `num_paths` where `num_paths[i]` = # of
//! paths in tree with `i` edges. `num_paths[1]` = # edges
//! @time O(n * log1.5(n) * log2(n))
//! @space this function allocates/returns various vectors
//! which are each O(n)
vector<ll> count_paths_per_length(const vector<vi>& adj) {
  vector<ll> num_paths(sz(adj));
  num_paths[1] = sz(adj) - 1;
  edge_cd(adj,
    [&](const vector<vi>& cd_adj, int cent, int split) {
      vector<vector<double>> cnt(2, vector<double>(1));
      auto dfs = [&](auto&& self, int v, int p, int d,
                   int side) -> void {
        if (sz(cnt[side]) == d) cnt[side].push_back(0.0);
        cnt[side][d]++;
        for (int u : cd_adj[v])
          if (u != p) self(self, u, v, 1 + d, side);
      };
      rep(i, 0, sz(cd_adj[cent]))
        dfs(dfs, cd_adj[cent][i], cent, 1, i < split);
      vector<double> prod = conv(cnt[0], cnt[1]);
      rep(i, 0, sz(prod)) num_paths[i] += llround(prod[i]);
    });
  return num_paths;
}
