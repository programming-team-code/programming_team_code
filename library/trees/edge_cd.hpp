#pragma once
//! https://codeforces.com/blog/entry/104997
//! https://codeforces.com/blog/entry/120446
//! https://codeforces.com/blog/entry/142176
//! https://youtu.be/wDwaMo5xa-k
//! @code
//!   vector<basic_string<int>> adj(n);
//!   edge_cd(adj, [&](const auto& adj, int cent, int m) {
//!     // subtrees of [0, m) of adj[cent]: 1st edge-set
//!     // subtrees of [m, sz(adj[cent])): 2nd edge-set
//!   });
//! @endcode
//! handle single-edge-paths separately
//! @time O(n logφ n)
//! @space O(n)
template<class F, class G> struct edge_cd {
  vector<G> adj;
  F f;
  vi siz;
  edge_cd(const vector<G>& adj, F f):
    adj(adj), f(f), siz(sz(adj)) {
    dfs(0, sz(adj) - 1);
  }
  int find_cent(int u, int p, int m) {
    siz[u] = 1;
    for (int v : adj[u])
      if (v != p) {
        int cent = find_cent(v, u, m);
        if (cent != -1) return cent;
        siz[u] += siz[v];
      }
    return 2 * siz[u] > m
           ? p >= 0 && (siz[p] = m + 1 - siz[u]),
           u : -1;
  }
  void dfs(int u, int m) {
    if (m < 2) return;
    u = find_cent(u, -1, m);
    int sum = 0;
    auto it = partition(all(adj[u]), [&](int v) {
      ll x = sum + siz[v];
      return x * x < m * (m - x) ? sum += siz[v], 1 : 0;
    });
    f(adj, u, it - begin(adj[u]));
    G oth(it, end(adj[u]));
    adj[u].erase(it, end(adj[u]));
    dfs(u, sum);
    swap(adj[u], oth);
    dfs(u, m - sum);
  }
};
