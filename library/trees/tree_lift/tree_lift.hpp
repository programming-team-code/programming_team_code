#pragma once
//! https://github.com/ucf-programming-team/hackpack-cpp/blob/master/content/graphs/TreeLifting.h
//! @code
//!   {
//!     vector<vi> adj(n);
//!     tree_lift tree_l(adj);
//!   }
//!   vector<basic_string<int>> adj(n);
//!   tree_lift tree_l(adj);
//!   tree_l.kth_par(v, k); // k edges up from v
//! @endcode
//! @time O(n + q log n)
//! @space O(n)
struct tree_lift {
  vi d, p, j;
  tree_lift(const auto& adj): d(sz(adj)), p(d), j(d) {
    auto dfs = [&](auto&& self, int v) -> void {
      int up =
        d[v] + d[j[j[v]]] == 2 * d[j[v]] ? j[j[v]] : v;
      for (int u : adj[v])
        if (u != p[v])
          d[u] = d[p[u] = v] + 1, j[u] = up, self(self, u);
    };
    dfs(dfs, 0);
  }
  int kth_par(int v, int k) {
    int anc_d = d[v] - k;
    while (d[v] > anc_d)
      v = d[j[v]] >= anc_d ? j[v] : p[v];
    return v;
  }
  int lca(int u, int v) {
    if (d[u] < d[v]) swap(u, v);
    u = kth_par(u, d[u] - d[v]);
    while (u != v)
      if (j[u] != j[v]) u = j[u], v = j[v];
      else u = p[u], v = p[v];
    return u;
  }
#include "../extra_members/dist_edges.hpp"
#include "kth_path.hpp"
};
