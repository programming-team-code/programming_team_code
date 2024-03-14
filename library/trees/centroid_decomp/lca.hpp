/** @file */
#pragma once
#include "centroid_decomp.hpp"
/**
 * @see https://codeforces.com/blog/entry/81661#comment-686024
 */
struct cd_lca {
  vector<int> d;
  vector<vector<int>> mn_d, to_cent;
  int cmp(int u, int v) { return d[u] < d[v] ? u : v; }
  /**
   * @param adj unrooted, undirected tree
   * @time O(n log n)
   * @space O(n log n) for `mn_d` and `to_cent` vectors
   */
  cd_lca(const vector<vector<int>>& adj) : d(ssize(adj)), mn_d(ssize(adj)), to_cent(ssize(adj)) {
    auto dfs_d = [&](auto&& self, int u, int p) -> void {
      for (int v : adj[u])
        if (v != p)
          d[v] = 1 + d[u], self(self, v, u);
    };
    dfs_d(dfs_d, 0, -1);
    centroid(adj, [&](const vector<vector<int>>& cd_adj, int cent) {
      auto dfs = [&](auto&& self, int u, int p) -> void {
        mn_d[u].push_back(p == -1 ? u : cmp(mn_d[p].back(), u));
        to_cent[u].push_back(cent);
        for (int v : cd_adj[u])
          if (v != p) self(self, v, u);
      };
      dfs(dfs, cent, -1);
    });
  }
  /**
   * @param u,v nodes
   * @returns lca of u, v; where the root is 0
   * @time O(log(n))
   * @space O(1)
   */
  int lca(int u, int v) {
    for (int i = min(ssize(mn_d[u]), ssize(mn_d[v])) - 1;; i--)
      if (to_cent[u][i] == to_cent[v][i])
        return cmp(mn_d[u][i], mn_d[v][i]);
  }
};
