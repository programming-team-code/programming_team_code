#pragma once
//! https://codeforces.com/blog/entry/104997
//! https://codeforces.com/blog/entry/120446
//! https://codeforces.com/blog/entry/142176
//! https://youtu.be/wDwaMo5xa-k
//! @code
//!   vector<basic_string<int>> g(n);
//!   edge_cd(g, [&](int cent, int m) {
//!     // subtrees of [0, m) of g[cent]: 1st edge-set
//!     // subtrees of [m, sz(g[cent])): 2nd edge-set
//!   });
//! @endcode
//! handle single-edge-paths separately
//! @time O(n logφ n)
//! @space O(n)
template<class G> void edge_cd(vector<G>& g, auto f) {
  vi siz(sz(g));
  auto cent = [&](auto&& cent, int u, int p,
                int m) -> int {
    siz[u] = 1;
    for (int v : g[u])
      if (v != p) {
        int c = cent(cent, v, u, m);
        if (c != -1) return c;
        siz[u] += siz[v];
      }
    return 2 * siz[u] > m ? siz[p] = m + 1 - siz[u],
                            u : -1;
  };
  auto dfs = [&](auto&& dfs, int u, int m) -> void {
    if (m < 2) return;
    u = cent(cent, u, u, m);
    int sum = 0;
    auto it = partition(all(g[u]), [&](int v) {
      ll x = sum + siz[v];
      return x * x < m * (m - x) ? sum = x : 0;
    });
    f(u, it - begin(g[u]));
    G oth(it, end(g[u]));
    g[u].erase(it, end(g[u]));
    dfs(dfs, u, sum);
    swap(g[u], oth);
    dfs(dfs, u, m - sum);
  };
  dfs(dfs, 0, sz(g) - 1);
};
