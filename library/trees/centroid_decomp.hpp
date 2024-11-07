#pragma once
//! @code
//!   centroid(adj, [&](const vector<vi>& adj,
//!     int cent) {
//!   });
//! @endcode
//! @time O(n log n)
//! @space O(n)
template<class F> struct centroid {
  vector<vi> adj;
  F f;
  vi siz, par;
  centroid(const vector<vi>& a_adj, F a_f):
    adj(a_adj), f(a_f), siz(sz(adj), -1), par(siz) {
    rep(i, 0, sz(adj)) if (siz[i] == -1) dfs(i);
  }
  void calc_sz(int v, int p) {
    siz[v] = 1;
    for (int u : adj[v])
      if (u != p) calc_sz(u, v), siz[v] += siz[u];
  }
  int dfs(int v) {
    calc_sz(v, -1);
    for (int p = -1, sz_root = siz[v];;) {
      auto big_ch = find_if(all(adj[v]), [&](int u) {
        return u != p && 2 * siz[u] > sz_root;
      });
      if (big_ch == end(adj[v])) break;
      p = v, v = *big_ch;
    }
    f(adj, v);
    for (int u : adj[v]) {
      iter_swap(find(all(adj[u]), v), rbegin(adj[u]));
      adj[u].pop_back();
      par[dfs(u)] = v;
    }
    return v;
  }
};
