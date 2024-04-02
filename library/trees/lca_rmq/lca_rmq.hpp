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
  vi in, sub_sz, d, p, order;
  RMQ<int, function<int(int, int)>> rmq;
  /**
   * @param adj forest (rooted or unrooted)
   * @time O(n log n)
   * @space O(n log n) for rmq, all other vectors are O(n)
   */
  LCA(const vector<vi>& adj) : n(sz(adj)), in(n), sub_sz(n, 1), d(n), p(n, -1) {
    auto dfs = [&](auto&& self, int u) -> void {
      in[u] = sz(order), order.push_back(u);
      for (int v : adj[u])
        if (v != p[u])
          d[v] = d[p[v] = u] + 1, self(self, v), sub_sz[u] += sub_sz[v];
    };
    order.reserve(n);
    rep(i, 0, n) if (p[i] == -1) dfs(dfs, i);
    rmq = {order, [&](int u, int v) { return d[u] < d[v] ? u : v; }};
  }
  /**
   * @param u,v 2 nodes in the same component
   * @returns lca of u, v
   * @time O(1)
   * @space O(1)
   */
  inline int lca(int u, int v) {
    if (u == v) return u;
    auto [x, y] = minmax(in[u], in[v]);
    return p[rmq.query(x + 1, y + 1)];
  }
#include "../dist_edges.hpp"
#include "in_subtree.hpp"
#include "next_on_path.hpp"
#include "../compress_tree.hpp"
};
