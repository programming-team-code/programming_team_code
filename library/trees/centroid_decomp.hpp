#pragma once
//! @code
//!   vector<basic_string<int>> g(n);
//!   vi par = cd(g, [&](int cent) {});
//! @endcode
//! @time O(n log n)
//! @space O(n)
vi cd(auto& g, auto f) {
  vi p(sz(g), -1), siz(sz(g), sz(g));
  auto ctd = [&](auto ctd, int u, int p, int n) -> int {
    siz[u] = 1;
    for (int v : g[u])
      if (v != p) {
        if (int c = ctd(ctd, v, u, n); c != -1) return c;
        siz[u] += siz[v];
      }
    return 2 * siz[u] >= n ? siz[p] = n - siz[u], u : -1;
  };
  auto dfs = [&](auto dfs, int u) -> int {
    f(u = ctd(ctd, u, u, siz[u]));
    for (int v : g[u]) erase(g[v], u), p[dfs(dfs, v)] = u;
    return u;
  };
  return dfs(dfs, 0), p;
}
