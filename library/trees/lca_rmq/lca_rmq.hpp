/** @file */
#pragma once
#include "../../monotonic_stack/monotonic_stack.hpp" /**< only needed for compress_tree */
#include "../../data_structures/rmq.hpp"
/**
 * @see https://github.com/kth-competitive-programming /kactl/blob/main/content/graph/LCA.h
 */
// NOLINTNEXTLINE(readability-identifier-naming)
struct LCA {
  int n;
  struct node {
    int in, sub_sz = 1, d, p = -1, order;
  };
  vector<node> t;
  RMQ<int, function<int(int, int)>> rmq;
  /**
   * @param adj forest (rooted or unrooted)
   * @time O(n log n)
   * @space O(n log n) for rmq, all other vectors are O(n)
   */
  LCA(const vector<vi>& adj) : n(sz(adj)), t(n) {
    int timer = 0;
    auto dfs = [&](auto&& self, int u) -> void {
      t[u].in = timer, t[timer++].order = u;
      for (int v : adj[u])
        if (v != t[u].p)
          t[v].d = t[t[v].p = u].d + 1, self(self, v), t[u].sub_sz += t[v].sub_sz;
    };
    rep(i, 0, n) if (t[i].p == -1) dfs(dfs, i);
    vi order(n);
    rep(i, 0, n) order[i] = t[i].order;
    rmq = {order, [&](int u, int v) { return t[u].d < t[v].d ? u : v; }};
  }
  /**
   * @param u,v 2 nodes in the same component
   * @returns lca of u, v
   * @time O(1)
   * @space O(1)
   */
  inline int lca(int u, int v) {
    if (u == v) return u;
    auto [x, y] = minmax(t[u].in, t[v].in);
    return t[rmq.query(x + 1, y + 1)].p;
  }
#include "../dist_edges.hpp"
#include "in_subtree.hpp"
#include "next_on_path.hpp"
#include "../compress_tree.hpp"
};
