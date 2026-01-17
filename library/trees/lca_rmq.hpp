#pragma once
#include "../monotonic_stack/monotonic_stack.hpp"
#include "../data_structures_[l,r)/rmq.hpp"
//! https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/LCA.h
//! @code
//!   vector<basic_string<int>> adj(n);
//!   LCA lca(adj);
//! @endcode
//! @time O(nlogn + q)
//! @space O(nlogn)
// NOLINTNEXTLINE(readability-identifier-naming)
struct LCA {
  int n;
  vi tin, siz, d, p;
  RMQ<int, function<int(int, int)>> rmq = {{}, NULL};
  LCA(const auto& adj):
    n(sz(adj)), tin(n), siz(n, 1), d(n), p(n) {
    vi order;
    auto dfs = [&](auto&& self, int u) -> void {
      tin[u] = sz(order), order.push_back(u);
      for (int v : adj[u])
        if (v != p[u])
          d[v] = d[p[v] = u] + 1, self(self, v),
          siz[u] += siz[v];
    };
    dfs(dfs, 0);
    rmq = {order,
      [&](int u, int v) { return d[u] < d[v] ? u : v; }};
  }
  int lca(int u, int v) {
    if (u == v) return u;
    auto [x, y] = minmax(tin[u], tin[v]);
    return p[rmq.query(x + 1, y + 1)];
  }
#include "extra_members/dist.hpp"
#include "extra_members/in_subtree.hpp"
#include "extra_members/on_path.hpp"
#include "extra_members/next_on_path.hpp"
#include "extra_members/virtual_tree.hpp"
};
