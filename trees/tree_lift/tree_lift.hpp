/**
 * @see https://github.com/ucf-programming-team/hackpack-cpp /blob/master/content/graphs/TreeLifting.h
 * Calculate jumps up a tree, to support fast upward jumps and LCAs.
 */
struct tree_lift {
  struct node {
    int d, p = -1, j = -1;
  };
  vector<node> t;
  /**
   * @param adj forest (rooted or unrooted)
   * @time O(n)
   * @space O(n) for d, p, j vectors
   */
  tree_lift(const vector<vector<int>>& adj) : t((int)size(adj)) {
    auto dfs = [&](auto&& self, int v) -> void {
      int jump = (t[v].d + t[t[t[v].j].j].d == 2 * t[t[v].j].d) ? t[t[v].j].j : v;
      for (int u : adj[v])
        if (u != t[v].p)
          t[u].d = t[t[u].p = v].d + 1, t[u].j = jump, self(self, u);
    };
    for (int i = 0; i < ((int)size(t)); i++)
      if (t[i].j == -1) t[i].j = i, dfs(dfs, i);
  }
  /**
   * @param v query node
   * @param k number of edges
   * @returns a node k edges up from v. With k=1, this returns v's parent.
   * @time O(log k)
   * @space O(1)
   */
  int kth_par(int v, int k) {
    int anc_d = t[v].d - k;
    while (t[v].d > anc_d) v = t[t[v].j].d >= anc_d ? t[v].j : t[v].p;
    return v;
  }
  /**
   * @param u,v 2 nodes in the same component
   * @returns lca of u, v
   * @time O(log(path length(u, v)))
   * @space O(1)
   */
  int lca(int u, int v) {
    if (t[u].d < t[v].d) swap(u, v);
    u = kth_par(u, t[u].d - t[v].d);
    while (u != v)
      if (t[u].j != t[v].j) u = t[u].j, v = t[v].j;
      else u = t[u].p, v = t[v].p;
    return u;
  }
  /**
   * @param u,v endpoint nodes of path
   * @returns number of edges on path
   * @time same as lca(u, v)
   * @space O(1)
   */
  int dist_edges(int u, int v) {
    return t[u].d + t[v].d - 2 * t[lca(u, v)].d;
  }
  /**
   * @param u,v endpoint nodes of path
   * @param k index into path
   * @returns the node vi({u,p[u],..,lca(u,v),..,p[v],v})[k], or -1, so u if k=0
   * @time same as lca(u, v), kth_par(u, k)
   * @space O(1)
   */
  int kth_path(int u, int v, int k) {
    int lca_d = t[lca(u, v)].d;
    int u_lca = t[u].d - lca_d;
    int v_lca = t[v].d - lca_d;
    if (k <= u_lca) return kth_par(u, k);
    if (k <= u_lca + v_lca) return kth_par(v, u_lca + v_lca - k);
    return -1;
  }
};
