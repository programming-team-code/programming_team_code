#pragma once
//! @code
//!   centroid(adj, [&](const vector<vi>& adj,
//!     int cent, int par_cent) {
//!   });
//! @endcode
//! @time O(n log n)
//! @space O(n)
template<class F> struct centroid {
  vector<vi> adj;
  F f;
  vi sub_sz;
  centroid(const vector<vi>& a_adj, F a_f):
    adj(a_adj), f(a_f), sub_sz(sz(adj), -1) {
    rep(i, 0, sz(adj)) if (sub_sz[i] == -1) dfs(i, -1);
  }
  void calc_sz(int v, int p) {
    sub_sz[v] = 1;
    for (int u : adj[v])
      if (u != p) calc_sz(u, v), sub_sz[v] += sub_sz[u];
  }
  void dfs(int v, int p) {
    calc_sz(v, -1);
    for (int w = -1, sz_root = sub_sz[v];;) {
      auto big_ch = find_if(all(adj[v]), [&](int u) {
        return u != w && 2 * sub_sz[u] > sz_root;
      });
      if (big_ch == end(adj[v])) break;
      w = v, v = *big_ch;
    }
    f(adj, v, p);
    for (int u : adj[v]) {
      iter_swap(find(all(adj[u]), v), rbegin(adj[u]));
      adj[u].pop_back();
      dfs(u, v);
    }
  }
};
