#pragma once
//! https://codeforces.com/blog/entry/125866?#comment-1117826
//! @code
//!   vector<basic_string<int>> g(n);
//!   vector<int> p = cd(g, [&](int c) {});
//! @endcode
//! g is mutated (edges removed)
//! @time O(n log n)
//! @space O(n)
vi cd(auto& g, auto f) {
  vi p(sz(g), -1), s(sz(g), sz(g));
  auto ctd = [&](this auto&& ctd, int u, int p,
               int n) -> int {
    s[u] = 1;
    for (int v : g[u])
      if (v != p) {
        if (int c = ctd(v, u, n); c != -1) return c;
        s[u] += s[v];
      }
    return 2 * s[u] >= n ? s[p] = n - s[u], u : -1;
  };
  auto dfs = [&](this auto&& dfs, int u) -> int {
    f(u = ctd(u, u, s[u]));
    for (int v : g[u]) erase(g[v], u), p[dfs(v)] = u;
    return u;
  };
  return dfs(0), p;
}
