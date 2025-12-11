#pragma once
//! https://github.com/ucf-programming-team/hackpack-cpp/blob/master/content/graphs/TreeLifting.h
//! @code
//!   vector<basic_string<int>> adj(n);
//!   tree_lift tree_l(adj);
//!   tree_l.kth_par(v, k); // k edges up from v
//!   tree_l.kth_par(v, 1); // v's parent
//! @endcode
//! @time O(n + q log n)
//! @space O(n)
struct tree_lift {
  vi d, p, j;
  tree_lift(const auto& adj): d(sz(adj)), p(d), j(d) {
    auto dfs = [&](auto&& self, int u) -> void {
      int up =
        d[u] + d[j[j[u]]] == 2 * d[j[u]] ? j[j[u]] : u;
      for (int v : adj[u])
        if (v != p[u])
          d[v] = d[p[v] = u] + 1, j[v] = up, self(self, v);
    };
    dfs(dfs, 0);
  }
  int kth_par(int u, int k) {
    int anc_d = d[u] - k;
    while (d[u] > anc_d)
      u = d[j[u]] >= anc_d ? j[u] : p[u];
    return u;
  }
  int lca(int u, int v) {
    if (d[u] < d[v]) swap(u, v);
    u = kth_par(u, d[u] - d[v]);
    while (u != v)
      if (j[u] != j[v]) u = j[u], v = j[v];
      else u = p[u], v = p[v];
    return u;
  }
#include "extra_members/dist.hpp"
};
