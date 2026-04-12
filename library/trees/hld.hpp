#pragma once
//! https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/HLD.h
//! @code
//!   vector<basic_string<int>> g(n);
//!   HLD<0> hld(g);
//!   hld.path(u, v, [&](int l, int r) { // [l, r)
//!   });
//!   auto [l, r] = hld.subtree(u); // [l, r)
//! @endcode
//! @time O(n + q log^2 n)
//! @space O(n)
// NOLINTNEXTLINE(readability-identifier-naming)
template<bool VALS_EDGES> struct HLD {
  int n;
  vi p, siz, rt, tin;
  HLD(auto& g): n(sz(g)), p(n), siz(n, 1), rt(n), tin(n) {
    auto dfs1 = [&](auto&& dfs1, int u) -> void {
      for (int& v : g[u]) {
        erase(g[v], p[v] = u);
        dfs1(dfs1, v);
        siz[u] += siz[v];
        if (siz[v] > siz[g[u][0]]) swap(v, g[u][0]);
      }
    };
    dfs1(dfs1, 0);
    int tim = 0;
    auto dfs2 = [&](auto&& dfs2, int u) -> void {
      tin[u] = tim++;
      for (int v : g[u]) {
        rt[v] = (v == g[u][0] ? rt[u] : v);
        dfs2(dfs2, v);
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
  pii subtree(int u) {
    return {tin[u] + VALS_EDGES, tin[u] + siz[u]};
  }
};
