//! @file
#pragma once
#include "../../../kactl/content/numerical/FastFourierTransform.h"
#include "centroid_decomp.hpp"
//! @param adj unrooted, connected forest
//! @returns array `num_paths` where `num_paths[i]` = # of paths in tree with `i`
//! edges. `num_paths[1]` = # edges
//! @time O(n log^2 n)
//! @space this function allocates/returns various vectors which are each O(n)
vector<ll> count_paths_per_length(const vector<vi>& adj) {
  vector<ll> num_paths(sz(adj));
  centroid(adj, [&](const vector<vi>& cd_adj, int cent) {
    vector<vector<double>> child_depths;
    for (int v : cd_adj[cent]) {
      child_depths.emplace_back(1, 0.0);
      for (queue<pii> q({{v, cent}}); !empty(q);) {
        child_depths.back().push_back(sz(q));
        queue<pii> new_q;
        while (!empty(q)) {
          auto [u, p] = q.front();
          q.pop();
          for (int w : cd_adj[u]) {
            if (w == p) continue;
            new_q.push({w, u});
          }
        }
        swap(q, new_q);
      }
    }
    sort(all(child_depths), [&](auto& x, auto& y) {
      return sz(x) < sz(y);
    });
    vector total_depth(1, 1.0);
    for (auto& cnt_depth : child_depths) {
      auto prod = conv(total_depth, cnt_depth);
      rep(i, 1, sz(prod))
          num_paths[i] += llround(prod[i]);
      total_depth.resize(sz(cnt_depth));
      rep(i, 1, sz(cnt_depth))
          total_depth[i] += cnt_depth[i];
    }
  });
  return num_paths;
}
