#pragma once
//! @code
//!   vector<vi> adj(n);
//!   centroid(adj, [&](const vector<vi>& adj,
//!     int cent, int par_cent) {
//!   });
//!   vector<basic_string<int>> adj1(n);
//!   centroid(adj1,
//!     [&](const vector<basic_string<int>>& adj1,
//!     int cent, int par_cent) {});
//! @endcode
//! @time O(n log n)
//! @space O(n)
template<class F, class G> struct centroid {
  G adj;
  F f;
  vi siz;
  centroid(const G& adj, F f):
    adj(adj), f(f), siz(sz(adj), -1) {
    rep(i, 0, sz(adj)) if (siz[i] == -1) dfs(i, -1);
  }
  void calc_sz(int v, int p) {
    siz[v] = 1;
    for (int u : adj[v])
      if (u != p) calc_sz(u, v), siz[v] += siz[u];
  }
  void dfs(int v, int p) {
    calc_sz(v, -1);
    for (int w = -1, sz_root = siz[v];;) {
      auto big_ch = ranges::find_if(adj[v], [&](int u) {
        return u != w && 2 * siz[u] > sz_root;
      });
      if (big_ch == end(adj[v])) break;
      w = v, v = *big_ch;
    }
    f(adj, v, p);
    for (int u : adj[v]) {
      iter_swap(ranges::find(adj[u], v), rbegin(adj[u]));
      adj[u].pop_back();
      dfs(u, v);
    }
  }
};
