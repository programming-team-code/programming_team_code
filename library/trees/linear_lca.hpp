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
    auto dfs = [&](auto&& self, int u, int p) -> void {
      t[u].p = p;
      order.push_back(u);
      t[u].in = t[u].label = sz(order);
      for (int v : adj[u])
        if (v != p) {
          t[v].d = 1 + t[u].d;
          self(self, v, u);
          head[t[v].label] = u;
          t[u].sub_sz += t[v].sub_sz;
          if (lsb(t[v].label) > lsb(t[u].label)) t[u].label = t[v].label;
        }
    };
    rep(i, 0, sz(t)) if (t[i].in == 0) dfs(dfs, i, i);
    for (int u : order) t[u].asc = lsb(t[u].label) | t[t[u].p].asc;
  }
  /**
   * @param u,v nodes
   * @returns lca of u, v
   * @time O(1)
   * @space O(1)
   */
  int lca(int u, int v) {
    int j = t[u].asc & t[v].asc & -(1 << __lg((t[u].label ^ t[v].label) | 1));
    if (int k = t[u].asc ^ j; k) k = 1 << __lg(k), u = head[(t[u].label & -k) | k];
    if (int k = t[v].asc ^ j; k) k = 1 << __lg(k), v = head[(t[v].label & -k) | k];
    return t[u].d < t[v].d ? u : v;
  }
#include "dist_edges.hpp"
#include "in_subtree.hpp"
#include "compress_tree.hpp"
};
