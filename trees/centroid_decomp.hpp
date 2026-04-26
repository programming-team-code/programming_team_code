//! @code
//!   vector<basic_string<int>> g(n);
//!   centroid(g, [&](int cent, int par_cent) {});
//! @endcode
//! @time O(n log n)
//! @space O(n)
void centroid(auto& g, auto f) {
  vector<int> siz(ssize(g));
  auto ctd = [&](auto ctd, int u, int p, int n) -> int {
    siz[u] = 1;
    for (int v : g[u])
      if (v != p) {
        if (int c = ctd(ctd, v, u, n); c != -1) return c;
        siz[u] += siz[v];
      }
    return 2 * siz[u] >= n ? siz[p] = n - siz[u], u : -1;
  };
  auto dfs = [&](auto dfs, int u, int p, int n) -> void {
    f(u = ctd(ctd, u, u, n), p);
    for (int v : g[u]) erase(g[v], u), dfs(dfs, v, u, siz[v]);
  };
  dfs(dfs, 0, -1, ssize(g));
}
