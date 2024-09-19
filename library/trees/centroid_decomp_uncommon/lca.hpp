#pragma once
#include "centroid_decomp.hpp"
//! https://codeforces.com/blog/entry/81661#comment-686024
struct cd_lca {
  vi d;
  vector<vi> mn_d, to_cent;
  int cmp(int u, int v) { return d[u] < d[v] ? u : v; }
  //! @param adj unrooted, undirected tree
  //! @time O(n log n)
  //! @space O(n log n) for `mn_d` and `to_cent` vectors
  cd_lca(const vector<vi>& adj):
    d(sz(adj)), mn_d(sz(adj)), to_cent(sz(adj)) {
    auto dfs_d = [&](auto&& self, int v, int p) -> void {
      for (int u : adj[v])
        if (u != p) d[u] = 1 + d[v], self(self, u, v);
    };
    dfs_d(dfs_d, 0, -1);
    centroid(adj, [&](const vector<vi>& cd_adj, int cent) {
      auto dfs = [&](auto&& self, int v, int p) -> void {
        mn_d[v].push_back(
          p == -1 ? v : cmp(mn_d[p].back(), v));
        to_cent[v].push_back(cent);
        for (int u : cd_adj[v])
          if (u != p) self(self, u, v);
      };
      dfs(dfs, cent, -1);
    });
  }
  //! @param u,v nodes
  //! @returns lca of u, v; where the root is 0
  //! @time O(log(n))
  //! @space O(1)
  int lca(int u, int v) {
    for (int i = min(sz(mn_d[u]), sz(mn_d[v])) - 1;; i--)
      if (to_cent[u][i] == to_cent[v][i])
        return cmp(mn_d[u][i], mn_d[v][i]);
  }
};