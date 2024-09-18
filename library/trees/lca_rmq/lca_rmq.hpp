//! @file
#pragma once
#include "../../monotonic_stack/monotonic_stack.hpp" //!< only needed for compress_tree
#include "../../data_structures/rmq.hpp"
//! @see https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/LCA.h
// NOLINTNEXTLINE(readability-identifier-naming)
struct LCA {
  struct node {
    int in, sub_sz = 1, d, p = -1;
  };
  vector<node> t;
  RMQ<int, function<int(int, int)>> rmq = {{}, nullptr};
  //! @param adj forest (rooted or unrooted)
  //! @time O(n log n)
  //! @space O(n log n) for rmq, all other vectors are O(n)
  LCA(const vector<vi>& adj): t(sz(adj)) {
    vi order;
    auto dfs = [&](auto&& self, int v) -> void {
      t[v].in = sz(order), order.push_back(v);
      for (int u : adj[v])
        if (u != t[v].p)
          t[u].d = t[t[u].p = v].d + 1, self(self, u),
          t[v].sub_sz += t[u].sub_sz;
    };
    rep(i, 0, sz(t)) if (t[i].p == -1) dfs(dfs, i);
    rmq = {order,
      [&](int v, int u) { return t[v].d < t[u].d ? v : u; }};
  }
  //! @param u,v 2 nodes in the same component
  //! @returns lca of u, v
  //! @time O(1)
  //! @space O(1)
  int lca(int v, int u) {
    if (v == u) return v;
    auto [x, y] = minmax(t[v].in, t[u].in);
    return t[rmq.query(x + 1, y + 1)].p;
  }
#include "../dist_edges.hpp"
#include "../in_subtree.hpp"
#include "next_on_path.hpp"
#include "../compress_tree.hpp"
};
