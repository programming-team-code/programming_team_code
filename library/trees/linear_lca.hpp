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
    auto dfs = [&](auto&& self, int v, int p) -> void {
      order.emplace_back(v, p);
      in[v] = sz(order);
      for (int u : adj[v])
        if (u != p) {
          d[u] = 1 + d[v];
          self(self, u, v);
          head[in[u]] = v;
          if (lsb(in[v]) < lsb(in[u])) in[v] = in[u];
        }
    };
    dfs(dfs, 0, 0);
    for (auto [v, p] : order) asc[v] = asc[p] | lsb(in[v]);
  }
  int lca(int u, int v) {
    if (unsigned i = in[u] ^ in[v]; i) {
      i = asc[u] & asc[v] & -bit_floor(i);
      if (unsigned b = asc[u] ^ i; b)
        b = bit_floor(b), u = head[(in[u] & -b) | b];
      if (unsigned b = asc[v] ^ i; b)
        b = bit_floor(b), v = head[(in[v] & -b) | b];
    }
    return d[u] < d[v] ? u : v;
  }
#include "extra_members/dist.hpp"
};
