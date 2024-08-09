/**
 * @code{.cpp}
       centroid(adj, [&](const vector<vi>& adj, int cent) {
       });
 * @endcode
 */
template <class F> struct centroid {
  vector<vector<int>> adj;
  F f;
  vector<int> sub_sz;
  /**
   * @param a_adj,a_f undirected forest and callback
   * @time O(n log n)
   * @space `adj` and `sub_sz` arrays take O(n); recursion stack for `dfs` is
   * O(log n); recursion stack for `calc_sz` is O(n)
   */
  centroid(const vector<vector<int>>& a_adj, F a_f)
      : adj(a_adj), f(a_f), sub_sz((int)size(adj), -1) {
    for (int i = 0; i < ((int)size(adj)); i++)
      if (sub_sz[i] == -1) dfs(i);
  }
  void calc_sz(int v, int p) {
    sub_sz[v] = 1;
    for (int u : adj[v])
      if (u != p)
        calc_sz(u, v), sub_sz[v] += sub_sz[u];
  }
  void dfs(int v) {
    calc_sz(v, -1);
    for (int p = -1, sz_root = sub_sz[v];;) {
      auto big_ch = find_if(begin(adj[v]), end(adj[v]), [&](int u) {
        return u != p && 2 * sub_sz[u] > sz_root;
      });
      if (big_ch == end(adj[v])) break;
      p = v, v = *big_ch;
    }
    f(adj, v);
    for (int u : adj[v]) {
      iter_swap(find(begin(adj[u]), end(adj[u]), v), rbegin(adj[u]));
      adj[u].pop_back();
      dfs(u);
    }
  }
};
