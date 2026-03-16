#pragma once
//! @code
//!   vector<basic_string<int>> adj(n);
//!   centroid(adj, [&](const auto& adj,
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
    dfs(0, -1);
  }
  void calc_sz(int u, int p) {
    siz[u] = 1;
    for (int v : adj[u])
      if (v != p) calc_sz(v, u), siz[u] += siz[v];
  }
  void dfs(int u, int p) {
    calc_sz(u, -1);
    for (int w = -1, sz_root = siz[u];;) {
      auto big_ch = ranges::find_if(adj[u], [&](int v) {
        return v != w && 2 * siz[v] > sz_root;
      });
      if (big_ch == end(adj[u])) break;
      w = u, u = *big_ch;
    }
    f(adj, u, p);
    for (int v : adj[u]) {
      iter_swap(ranges::find(adj[v], u), rbegin(adj[v]));
      adj[v].pop_back();
      dfs(v, u);
    }
  }
};
