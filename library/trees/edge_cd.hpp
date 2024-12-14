#pragma once
//! https://codeforces.com/blog/entry/104997
//! https://codeforces.com/blog/entry/120446
//! https://youtu.be/wDwaMo5xa-k
//! @code
//!   vector<vi> adj(n);
//!   edge_cd(adj, [&](const vector<vi>& adj,
//!     int cent, int split) {
//!     // subtrees of prefix [0, split) of adj[cent]
//!     //   are the first edge-set
//!     // subtrees of suffix [split, sz(adj[cent]))
//!     //   of adj[cent] are the second edge-set
//!   });
//! @endcode
//! handle single-edge-paths separately
//! @time O(n log1.5 n)
//! @space O(n)
template<class F> struct edge_cd {
  vector<vi> adj;
  F f;
  vi sub_sz;
  edge_cd(const vector<vi>& adj, F f):
    adj(adj), f(f), sub_sz(sz(adj)) {
    dfs(0, sz(adj));
  }
  int find_cent(int v, int p, int siz) {
    sub_sz[v] = 1;
    for (int u : adj[v])
      if (u != p) {
        int cent = find_cent(u, v, siz);
        if (cent != -1) return cent;
        sub_sz[v] += sub_sz[u];
      }
    if (p == -1) return v;
    return 2 * sub_sz[v] >= siz
           ? sub_sz[p] = siz - sub_sz[v],
             v : -1;
  }
  void dfs(int v, int siz) {
    if (siz <= 2) return;
    v = find_cent(v, -1, siz);
    int sum = 0;
    auto it = partition(all(adj[v]), [&](int u) {
      bool ret = 2 * sum + sub_sz[u] < siz - 1 &&
        3 * (sum + sub_sz[u]) <= 2 * (siz - 1);
      if (ret) sum += sub_sz[u];
      return ret;
    });
    f(adj, v, it - begin(adj[v]));
    vi oth(it, end(adj[v]));
    adj[v].erase(it, end(adj[v]));
    dfs(v, sum + 1);
    swap(adj[v], oth);
    dfs(v, siz - sum);
  }
};
