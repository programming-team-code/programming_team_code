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
  int n;
  vector<int> d, p, head, in, order, big_ch;
  vector<unsigned> label, asc;
  /**
   * @param adj forest (rooted or unrooted)
   * @time O(n)
   * @space O(n)
   */
  linear_lca(const vector<vector<int>>& adj) : n(size(adj)), d(n), p(n), head(n + 1), in(n), big_ch(n), label(n), asc(n) {
    auto dfs = [&](auto&& self, int u) -> void {
      order.push_back(u);
      in[u] = label[u] = sz(order);
      for (int v : adj[u])
        if (v != p[u]) {
          d[v] = 1 + d[p[v] = u];
          self(self, v);
          if (lsb(label[v]) > lsb(label[u]))
            label[u] = label[big_ch[u] = v];
        }
      head[label[u]] = u;
    };
    for (int i = 0; i < n; i++)
      if (in[i] == 0) p[i] = i, dfs(dfs, i);
    for (int u : order) asc[u] = lsb(label[u]) | asc[p[u]];
  }
  inline int lift(int u, unsigned j) {
    auto k = bit_floor(asc[u] ^ j);
    return k == 0 ? u : p[head[(label[u] & -k) | k]];
  }
  /**
   * @param u,v nodes
   * @returns lca of u, v
   * @time O(1)
   * @space O(1)
   */
  inline int lca(int u, int v) {
    auto [x, y] = minmax(label[u], label[v]);
    auto j = asc[u] & asc[v] & -bit_floor((x - 1) ^ y);
    return d[u = lift(u, j)] < d[v = lift(v, j)] ? u : v;
  }
#include "../dist_edges.hpp"
#include "in_subtree.hpp"
#include "next_on_path.hpp"
#include "../compress_tree.hpp"
};
