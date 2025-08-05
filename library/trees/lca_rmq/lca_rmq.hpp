#pragma once
#include "../../data_structures/rmq.hpp"
//! https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/LCA.h
//! @code
//!   {
//!     vector<vi> adj(n);
//!     LCA lca(adj);
//!   }
//!   vector<basic_string<int>> adj(n);
//!   LCA lca(adj);
//! @endcode
//! @time O(nlogn + q)
//! @space O(nlogn)
// NOLINTNEXTLINE(readability-identifier-naming)
struct LCA {
  int n;
  vi in, siz, d, p;
  RMQ<int, function<int(int, int)>> rmq = {{}, NULL};
  LCA(const auto& adj):
    n(sz(adj)), in(n), siz(n, 1), d(n), p(n) {
    vi order;
    auto dfs = [&](auto&& self, int v) -> void {
      in[v] = sz(order), order.push_back(v);
      for (int u : adj[v])
        if (u != p[v])
          d[u] = d[p[u] = v] + 1, self(self, u),
          siz[v] += siz[u];
    };
    dfs(dfs, 0);
    rmq = {order,
      [&](int u, int v) { return d[u] < d[v] ? u : v; }};
  }
  int lca(int u, int v) {
    if (u == v) return u;
    auto [x, y] = minmax(in[u], in[v]);
    return p[rmq.query(x + 1, y + 1)];
  }
#include "../extra_members/dist_edges.hpp"
#include "../extra_members/in_subtree.hpp"
#include "../extra_members/on_path.hpp"
#include "next_on_path.hpp"
#include "../extra_members/compress_tree.hpp"
};
