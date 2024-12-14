#pragma once
#include "../../data_structures/rmq.hpp"
//! https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/LCA.h
//! @code
//!   vector<vi> adj(n);
//!   LCA lca(adj);
//! @endcode
//! @time O(nlogn + q)
//! @space O(nlogn)
// NOLINTNEXTLINE(readability-identifier-naming)
struct LCA {
  struct node {
    int in, sub_sz = 1, d, p = -1;
  };
  vector<node> t;
  RMQ<int, function<int(int, int)>> rmq = {{}, NULL};
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
    rmq = {order, [&](int u, int v) {
             return t[u].d < t[v].d ? u : v;
           }};
  }
  int lca(int u, int v) {
    if (u == v) return u;
    auto [x, y] = minmax(t[u].in, t[v].in);
    return t[rmq.query(x + 1, y + 1)].p;
  }
#include "../extra_members/dist_edges.hpp"
#include "../extra_members/in_subtree.hpp"
#include "../extra_members/on_path.hpp"
#include "next_on_path.hpp"
#include "../extra_members/compress_tree.hpp"
};
