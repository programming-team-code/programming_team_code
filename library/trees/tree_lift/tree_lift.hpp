/** @file */
#pragma once
/**
 * @see https://github.com/ucf-programming-team/hackpack-cpp /blob/master/content/graphs/TreeLifting.h
 * Calculate jumps up a tree, to support fast upward jumps and LCAs.
 */
struct tree_lift {
  struct node {
    int d, p = -1, j = -1;
  };
  vector<node> t;
  /**
   * @param adj forest (rooted or unrooted)
   * @time O(n)
   * @space O(n) for d, p, j vectors
   */
  tree_lift(const vector<vi>& adj) : t(sz(adj)) {
    auto dfs = [&](auto&& self, int u) -> void {
      int jump = (t[u].d + t[t[t[u].j].j].d == 2 * t[t[u].j].d) ? t[t[u].j].j : u;
      for (int v : adj[u])
        if (v != t[u].p)
          t[v].d = t[t[v].p = u].d + 1, t[v].j = jump, self(self, v);
    };
    rep(i, 0, sz(t)) if (t[i].j == -1) t[i].j = i, dfs(dfs, i);
  }
  /**
   * @param u query node
   * @param k number of edges
   * @returns a node k edges up from u. With k=1, this returns u's parent.
   * @time O(log k)
   * @space O(1)
   */
  int kth_par(int u, int k) {
    assert(0 <= k && k <= t[u].d);
    int anc_d = t[u].d - k;
    while (t[u].d > anc_d) u = t[t[u].j].d >= anc_d ? t[u].j : t[u].p;
    return u;
  }
  /**
   * @param u,v 2 nodes in the same component
   * @returns lca of u, v
   * @time O(log(path length(u, v)))
   * @space O(1)
   */
  int lca(int u, int v) {
    if (t[u].d < t[v].d) swap(u, v);
    u = kth_par(u, t[u].d - t[v].d);
    while (u != v)
      if (t[u].j != t[v].j) u = t[u].j, v = t[v].j;
      else u = t[u].p, v = t[v].p;
    return u;
  }
#include "../dist_edges.hpp"
#include "kth_path.hpp"
};
