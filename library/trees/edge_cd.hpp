#pragma once
//! https://codeforces.com/blog/entry/104997
//! https://codeforces.com/blog/entry/120446
//! https://codeforces.com/blog/entry/142176
//! https://youtu.be/wDwaMo5xa-k
//! @code
//!   {
//!     vector<vi> adj(n);
//!     edge_cd(adj, [&](const auto& adj,
//!       int cent, int m) {});
//!   }
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
  int find_cent(int v, int p, int m) {
    siz[v] = 1;
    for (int u : adj[v])
      if (u != p) {
        int cent = find_cent(u, v, m);
        if (cent != -1) return cent;
        siz[v] += siz[u];
      }
    return 2 * siz[v] > m
           ? p >= 0 && (siz[p] = m + 1 - siz[v]),
           v : -1;
  }
  void dfs(int v, int m) {
    if (m < 2) return;
    v = find_cent(v, -1, m);
    int sum = 0;
    auto it = partition(all(adj[v]), [&](int u) {
      ll x = sum + siz[u];
      return x * x < m * (m - x) ? sum += siz[u], 1 : 0;
    });
    f(adj, v, it - begin(adj[v]));
    G oth(it, end(adj[v]));
    adj[v].erase(it, end(adj[v]));
    dfs(v, sum);
    swap(adj[v], oth);
    dfs(v, m - sum);
  }
};
