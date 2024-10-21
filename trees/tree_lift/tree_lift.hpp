//! https://github.com/ucf-programming-team/hackpack-cpp/blob/master/content/graphs/TreeLifting.h
//! @code
//!   tree_lift tree_l(adj);
//!   int kth_p = tree_l.kth_par(v, k);
//! @endcode
//! kth_p = a node k edges up from v
//! @time O(n + q log n)
//! @space O(n)
struct tree_lift {
  struct node {
    int d, p = -1, j = -1;
  };
  vector<node> t;
  tree_lift(const vector<vector<int>>& adj):
    t(ssize(adj)) {
    auto dfs = [&](auto&& self, int v) -> void {
      int jump =
        (t[v].d + t[t[t[v].j].j].d == 2 * t[t[v].j].d)
        ? t[t[v].j].j
        : v;
      for (int u : adj[v])
        if (u != t[v].p)
          t[u].d = t[t[u].p = v].d + 1, t[u].j = jump,
          self(self, u);
    };
    for (int i = 0; i < ssize(t); i++)
      if (t[i].j == -1) t[i].j = i, dfs(dfs, i);
  }
  int kth_par(int v, int k) {
    int anc_d = t[v].d - k;
    while (t[v].d > anc_d)
      v = t[t[v].j].d >= anc_d ? t[v].j : t[v].p;
    return v;
  }
  int lca(int u, int v) {
    if (t[u].d < t[v].d) swap(u, v);
    u = kth_par(u, t[u].d - t[v].d);
    while (u != v)
      if (t[u].j != t[v].j) u = t[u].j, v = t[v].j;
      else u = t[u].p, v = t[v].p;
    return u;
  }
  int dist_edges(int u, int v) {
    return t[u].d + t[v].d - 2 * t[lca(u, v)].d;
  }
  //! returns the node
  //! vi({u,p[u],..,lca(u,v),..,p[v],v})[k]
  //! @time same as lca(u, v), kth_par(u, k)
  //! @space O(1)
  int kth_path(int u, int v, int k) {
    int lca_d = t[lca(u, v)].d;
    int u_lca = t[u].d - lca_d;
    int v_lca = t[v].d - lca_d;
    if (k <= u_lca) return kth_par(u, k);
    if (k <= u_lca + v_lca)
      return kth_par(v, u_lca + v_lca - k);
    return -1;
  }
};
