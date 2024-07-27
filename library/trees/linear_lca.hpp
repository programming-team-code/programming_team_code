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
    auto dfs = [&](auto&& self, int u) -> void {
      order.push_back(u);
      t[u].in = t[u].label = sz(order);
      for (int v : adj[u])
        if (v != t[u].p) {
          t[v].d = 1 + t[t[v].p = u].d;
          self(self, v);
          t[u].sub_sz += t[v].sub_sz;
          if (lsb(t[v].label) > lsb(t[u].label)) t[u].label = t[v].label;
        }
      head[t[u].label] = u;
    };
    rep(i, 0, sz(t)) if (t[i].in == 0) t[i].p = i, dfs(dfs, i);
    for (int u : order) t[u].asc = lsb(t[u].label) | t[t[u].p].asc;
  }
  int lift(int u, int k) { return k = 1 << __lg(k), head[(t[u].label & -k) | k]; }
  /**
   * @param u,v nodes
   * @returns lca of u, v
   * @time O(1)
   * @space O(1)
   */
  int lca(int u, int v) {
    int j = t[u].asc & t[v].asc & -(1 << __lg((t[u].label ^ t[v].label) | 1));
    if (int k = t[u].asc ^ j; k) u = t[lift(u, k)].p;
    if (int k = t[v].asc ^ j; k) v = t[lift(v, k)].p;
    return t[u].d < t[v].d ? u : v;
  }
#include "dist_edges.hpp"
#include "in_subtree.hpp"
#include "compress_tree.hpp"
};
