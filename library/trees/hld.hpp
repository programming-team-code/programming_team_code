#pragma once
//! https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/HLD.h
//! @code
//!   vector<basic_string<int>> adj(n);
//!   HLD<0> hld(adj);
//!   hld.path(u, v, [&](int l, int r) { // [l, r)
//!   });
//!   auto [l, r] = hld.subtree(v); // [l, r)
//! @endcode
//! @time O(n + q log^2 n)
//! @space O(n)
// NOLINTNEXTLINE(readability-identifier-naming)
template<bool VALS_EDGES> struct HLD {
  int n;
  vi p, siz, rt, tin;
  HLD(auto& adj):
    n(sz(adj)), p(n), siz(n, 1), rt(n), tin(n) {
    auto dfs1 = [&](auto&& self, int v) -> void {
      for (int& u : adj[v]) {
        iter_swap(ranges::find(adj[u], v), rbegin(adj[u]));
        adj[u].pop_back();
        p[u] = v;
        self(self, u);
        siz[v] += siz[u];
        if (siz[u] > siz[adj[v][0]]) swap(u, adj[v][0]);
      }
    };
    dfs1(dfs1, 0);
    int tim = 0;
    auto dfs2 = [&](auto&& self, int v) -> void {
      tin[v] = tim++;
      for (int u : adj[v]) {
        rt[u] = (u == adj[v][0] ? rt[v] : u);
        self(self, u);
      }
    };
    dfs2(dfs2, 0);
  }
  void path(int u, int v, auto f) {
    for (;; v = p[rt[v]]) {
      if (tin[u] > tin[v]) swap(u, v);
      if (rt[u] == rt[v]) break;
      f(tin[rt[v]], tin[v] + 1);
    }
    f(tin[u] + VALS_EDGES, tin[v] + 1);
  }
  pii subtree(int v) {
    return {tin[v] + VALS_EDGES, tin[v] + siz[v]};
  }
};
