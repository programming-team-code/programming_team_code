#pragma once
//! @code
//!   vector<basic_string<int>> g(n);
//!   centroid(g, [&](int cent, int par_cent) {});
//! @endcode
//! @time O(n log n)
//! @space O(n)
void centroid(auto& g, const auto& f) {
  vi siz(sz(g));
  auto calc_sz = [&](auto&& self, int u, int p) -> void {
    siz[u] = 1;
    for (int v : g[u])
      if (v != p) self(self, v, u), siz[u] += siz[v];
  };
  auto dfs = [&](auto&& self, int u, int p) -> void {
    calc_sz(calc_sz, u, -1);
    for (int w = -1, sz_root = siz[u];;) {
      auto big_ch = ranges::find_if(g[u], [&](int v) {
        return v != w && 2 * siz[v] > sz_root;
      });
      if (big_ch == end(g[u])) break;
      w = u, u = *big_ch;
    }
    f(u, p);
    for (int v : g[u]) {
      iter_swap(ranges::find(g[v], u), rbegin(g[v]));
      g[v].pop_back();
      self(self, v, u);
    }
  };
  dfs(dfs, 0, -1);
}
