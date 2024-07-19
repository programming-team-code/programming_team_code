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
    int d, p, head, in, order, big_ch;
    unsigned label, asc;
  };
  vector<node> t;
  /**
   * @param adj forest (rooted or unrooted)
   * @time O(n)
   * @space O(n)
   */
  linear_lca(const vector<vi>& adj) : t(sz(adj)) {
    int timer = 0;
    auto dfs = [&](auto&& self, int u) -> void {
      t[timer++].order = u;
      t[u].in = t[u].label = timer;
      for (int v : adj[u])
        if (v != t[u].p) {
          t[v].d = 1 + t[t[v].p = u].d;
          self(self, v);
          if (lsb(t[v].label) > lsb(t[u].label))
            t[u].label = t[t[u].big_ch = v].label;
        }
      t[t[u].label - 1].head = u;
    };
    rep(i, 0, sz(t)) if (t[i].in == 0) t[i].p = i, dfs(dfs, i);
    rep(i, 0, sz(t)) t[t[i].order].asc = lsb(t[t[i].order].label) | t[t[t[i].order].p].asc;
  }
  inline int lift(int u, unsigned j) {
    auto k = bit_floor(t[u].asc ^ j);
    return k == 0 ? u : t[t[((t[u].label & -k) | k) - 1].head].p;
  }
  /**
   * @param u,v nodes
   * @returns lca of u, v
   * @time O(1)
   * @space O(1)
   */
  inline int lca(int u, int v) {
    auto [x, y] = minmax(t[u].label, t[v].label);
    auto j = t[u].asc & t[v].asc & -bit_floor((x - 1) ^ y);
    return t[u = lift(u, j)].d < t[v = lift(v, j)].d ? u : v;
  }
#include "../dist_edges.hpp"
#include "in_subtree.hpp"
#include "next_on_path.hpp"
#include "../compress_tree.hpp"
};
