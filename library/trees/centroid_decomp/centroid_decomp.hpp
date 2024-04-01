/** @file */
#pragma once
/**
 * @code{.cpp}
       centroid(adj, [&](const vector<vi>& adj, int cent) {
       });
 * @endcode
 */
template <class F> struct centroid {
  vector<vi> adj;
  F f;
  vi sub_sz;
  /**
   * @param a_adj,a_f undirected forest and callback
   * @time O(n log n)
   * @space `adj` and `sub_sz` arrays take O(n); recursion stack for `dfs` is
   * O(log n); recursion stack for `calc_sz` is O(n)
   */
  centroid(const vector<vi>& a_adj, F a_f)
      : adj(a_adj), f(a_f), sub_sz(sz(adj), -1) {
    for (int i = 0; i < sz(adj); i++)
      if (sub_sz[i] == -1) dfs(i);
  }
  void calc_sz(int u, int p) {
    sub_sz[u] = 1;
    for (int v : adj[u])
      if (v != p)
        calc_sz(v, u), sub_sz[u] += sub_sz[v];
  }
  void dfs(int u) {
    calc_sz(u, -1);
    for (int p = -1, sz_root = sub_sz[u];;) {
      auto big_ch = find_if(begin(adj[u]), end(adj[u]), [&](int v) {
        return v != p && 2 * sub_sz[v] > sz_root;
      });
      if (big_ch == end(adj[u])) break;
      p = u, u = *big_ch;
    }
    f(adj, u);
    for (int v : adj[u]) {
      iter_swap(find(begin(adj[v]), end(adj[v]), u), rbegin(adj[v]));
      adj[v].pop_back();
      dfs(v);
    }
  }
};
