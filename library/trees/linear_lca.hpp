#pragma once
//! https://codeforces.com/blog/entry/125371
//! @code
//!   vector<basic_string<int>> adj(n);
//!   linear_lca llca(adj);
//! @endcode
//! @time O(n + q)
//! @space O(n)
int lsb(int x) { return x & -x; }
struct linear_lca {
  int n;
  vi d, in, asc, head;
  linear_lca(const auto& adj):
    n(sz(adj)), d(n), in(n), asc(n), head(n + 1) {
    vector<pii> order;
    auto dfs = [&](auto&& self, int u, int p) -> void {
      order.emplace_back(u, p);
      in[u] = sz(order);
      for (int v : adj[u])
        if (v != p) {
          d[v] = 1 + d[u];
          self(self, v, u);
          head[in[v]] = u;
          if (lsb(in[u]) < lsb(in[v])) in[u] = in[v];
        }
    };
    dfs(dfs, 0, 0);
    for (auto [u, p] : order) asc[u] = asc[p] | lsb(in[u]);
  }
  int lca(int u, int v) {
    if (unsigned j = in[u] ^ in[v]; j) {
      j = asc[u] & asc[v] & -bit_floor(j);
      if (unsigned k = asc[u] ^ j; k)
        k = bit_floor(k), u = head[(in[u] & -k) | k];
      if (unsigned k = asc[v] ^ j; k)
        k = bit_floor(k), v = head[(in[v] & -k) | k];
    }
    return d[u] < d[v] ? u : v;
  }
#include "extra_members/dist.hpp"
};
