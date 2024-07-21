/** @file */
#pragma once
#include "../../monotonic_stack/monotonic_stack.hpp" /**< only needed for compress_tree */
inline int bit_floor(unsigned x) { return x ? 1 << __lg(x) : 0; }
inline int lsb(int x) { return x & -x; }
/**
 * @see On Finding Lowest Common Ancestors: Simplification and Parallelization
 * by Baruch Schieber, Uzi Vishkin, April 1987
 */
struct linear_lca {
  struct node {
    int d, p, in, big_ch;
    unsigned label, asc;
  };
  vector<node> t;
  vector<int> head, order;
  /**
   * @param adj forest (rooted or unrooted)
   * @time O(n)
   * @space O(n)
   */
  linear_lca(const vector<vi>& adj) : t(sz(adj)), head(sz(adj) + 1) {
    auto dfs = [&](auto&& self, int u) -> void {
      order.push_back(u);
      t[u].in = t[u].label = sz(order);
      for (int v : adj[u])
        if (v != t[u].p) {
          t[v].d = 1 + t[t[v].p = u].d;
          self(self, v);
          if (lsb(t[v].label) > lsb(t[u].label))
            t[u].label = t[t[u].big_ch = v].label;
        }
      head[t[u].label] = u;
    };
    rep(i, 0, sz(t)) if (t[i].in == 0) t[i].p = i, dfs(dfs, i);
    for (int u : order) t[u].asc = lsb(t[u].label) | t[t[u].p].asc;
  }
  inline int lift(int u, unsigned j) {
    auto k = bit_floor(t[u].asc ^ j);
    return k == 0 ? u : t[head[(t[u].label & -k) | k]].p;
  }
  /**
   * @param u,v nodes
   * @returns lca of u, v
   * @time O(1)
   * @space O(1)
   */
  inline int lca(int u, int v) {
    auto j = t[u].asc & t[v].asc & -bit_floor((t[u].label ^ t[v].label) | 1);
    return t[u = lift(u, j)].d < t[v = lift(v, j)].d ? u : v;
  }
#include "../dist_edges.hpp"
#include "in_subtree.hpp"
#include "next_on_path.hpp"
#include "../compress_tree.hpp"
};
