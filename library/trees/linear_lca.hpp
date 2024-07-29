/** @file */
#pragma once
#include "../monotonic_stack/monotonic_stack.hpp" /**< only needed for compress_tree */
int lsb(int x) { return x & -x; }
/**
 * @see On Finding Lowest Common Ancestors: Simplification and Parallelization
 * by Baruch Schieber, Uzi Vishkin, April 1987
 */
struct linear_lca {
  struct node {
    int d, p, sub_sz = 1, in, label, asc;
  };
  vector<node> t;
  vi head;
  /**
   * @param adj forest (rooted or unrooted)
   * @time O(n)
   * @space O(n)
   */
  linear_lca(const vector<vi>& adj) : t(sz(adj)), head(sz(adj) + 1) {
    vi order;
    auto dfs = [&](auto&& self, int v, int p) -> void {
      order.push_back(v);
      t[v].p = p, t[v].in = t[v].label = sz(order);
      for (int u : adj[v])
        if (u != p) {
          t[u].d = 1 + t[v].d;
          self(self, u, v);
          head[t[u].label] = v;
          t[v].sub_sz += t[u].sub_sz;
          if (lsb(t[u].label) > lsb(t[v].label)) t[v].label = t[u].label;
        }
    };
    rep(i, 0, sz(t)) if (t[i].in == 0) dfs(dfs, i, i);
    for (int v : order) t[v].asc = lsb(t[v].label) | t[t[v].p].asc;
  }
  /**
   * @param u,v nodes
   * @returns lca of u, v
   * @time O(1)
   * @space O(1)
   */
  int lca(int u, int v) {
    if (int j = t[u].label ^ t[v].label; j) {
      j = t[u].asc & t[v].asc & -(1 << __lg(j));
      if (int k = t[u].asc ^ j; k) k = 1 << __lg(k), u = head[(t[u].label & -k) | k];
      if (int k = t[v].asc ^ j; k) k = 1 << __lg(k), v = head[(t[v].label & -k) | k];
    }
    return t[u].d < t[v].d ? u : v;
  }
#include "dist_edges.hpp"
#include "in_subtree.hpp"
#include "compress_tree.hpp"
};
