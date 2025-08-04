#pragma once
//! https://codeforces.com/blog/entry/125371
//! @code
//!   {
//!     vector<vi> adj(n);
//!     linear_lca llca(adj);
//!   }
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
    if (unsigned j = in[u] ^ in[v]; j) {
      j = asc[u] & asc[v] & -bit_floor(j);
      if (unsigned k = asc[u] ^ j; k)
        k = bit_floor(k), u = head[(in[u] & -k) | k];
      if (unsigned k = asc[v] ^ j; k)
        k = bit_floor(k), v = head[(in[v] & -k) | k];
    }
    return d[u] < d[v] ? u : v;
  }
};
