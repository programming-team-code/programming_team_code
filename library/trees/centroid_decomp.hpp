#pragma once
//! https://codeforces.com/blog/entry/125866?#comment-1117826
//! @code
//!   vector<basic_string<int>> g(n);
//!   vi p = cd(g, [&](int c) {});
//! @endcode
//! @time O(n log n)
//! @space O(n)
vi cd(auto& g, auto f) {
  vi p(sz(g), -1), s(sz(g), sz(g));
  auto ctd = [&](auto ctd, int u, int p, int n) -> int {
    s[u] = 1;
    for (int v : g[u])
      if (v != p) {
        if (int c = ctd(ctd, v, u, n); c != -1) return c;
        s[u] += s[v];
      }
    return 2 * s[u] >= n ? s[p] = n - s[u], u : -1;
  };
  auto dfs = [&](auto dfs, int u) -> int {
    f(u = ctd(ctd, u, u, s[u]));
    for (int v : g[u]) erase(g[v], u), p[dfs(dfs, v)] = u;
    return u;
  };
  return dfs(dfs, 0), p;
}
