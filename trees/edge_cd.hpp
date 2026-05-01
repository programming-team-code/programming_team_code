//! https://codeforces.com/blog/entry/104997
//! https://codeforces.com/blog/entry/120446
//! https://codeforces.com/blog/entry/142176
//! https://youtu.be/wDwaMo5xa-k
//! @code
//!   vector<basic_string<int>> g(n);
//!   edge_cd(g, [&](int c, int m) {
//!     // subtrees of [0, m) of g[c]: 1st edge-set
//!     // subtrees of [m, sz(g[c])): 2nd edge-set
//!   });
//! @endcode
//! handle single-edge-paths separately
//! @time O(n logφ n)
//! @space O(n)
template<class G> void edge_cd(vector<G>& g, auto f) {
  vector<int> s(ssize(g));
  auto ctd = [&](auto ctd, int u, int p, int m) -> int {
    s[u] = 1;
    for (int v : g[u])
      if (v != p) {
        if (int c = ctd(ctd, v, u, m); c != -1) return c;
        s[u] += s[v];
      }
    return 2 * s[u] > m ? s[p] = m + 1 - s[u], u : -1;
  };
  auto dfs = [&](auto dfs, int u, int m) {
    if (m < 2) return;
    u = ctd(ctd, u, u, m);
    int sum = 0;
    auto it = partition(begin(g[u]), end(g[u]), [&](int v) {
      int64_t x = sum + s[v];
      return x * x < m * (m - x) ? sum = x : 0;
    });
    f(u, it - begin(g[u]));
    G oth(it, end(g[u]));
    g[u].erase(it, end(g[u]));
    dfs(dfs, u, sum);
    swap(g[u], oth);
    dfs(dfs, u, m - sum);
  };
  dfs(dfs, 0, ssize(g) - 1);
};
