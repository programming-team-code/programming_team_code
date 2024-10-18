//! https://codeforces.com/blog/entry/125371
//! @time O(n + q)
//! @space O(n)
int lsb(int x) { return x & -x; }
struct linear_lca {
  struct node {
    int d, label, asc;
  };
  vector<node> t;
  vector<int> head;
  linear_lca(const vector<vector<int>>& adj):
    t((int)size(adj)), head((int)size(t) + 1) {
    vector<pair<int, int>> order;
    auto dfs = [&](auto&& self, int v, int p) -> void {
      order.emplace_back(v, p);
      t[v].label = (int)size(order);
      for (int u : adj[v])
        if (u != p) {
          t[u].d = 1 + t[v].d;
          self(self, u, v);
          head[t[u].label] = v;
          if (lsb(t[u].label) > lsb(t[v].label))
            t[v].label = t[u].label;
        }
    };
    for (int i = 0; i < ((int)size(t)); i++)
      if (t[i].d == 0) dfs(dfs, i, i);
    for (auto [v, p] : order)
      t[v].asc = t[p].asc | lsb(t[v].label);
  }
  int lca(int u, int v) {
    if (int j = t[u].label ^ t[v].label; j) {
      j = t[u].asc & t[v].asc & -(1 << __lg(j));
      if (int k = t[u].asc ^ j; k)
        k = 1 << __lg(k), u = head[(t[u].label & -k) | k];
      if (int k = t[v].asc ^ j; k)
        k = 1 << __lg(k), v = head[(t[v].label & -k) | k];
    }
    return t[u].d < t[v].d ? u : v;
  }
  int dist_edges(int u, int v) {
    return t[u].d + t[v].d - 2 * t[lca(u, v)].d;
  }
};
//! https://codeforces.com/blog/entry/126580
//! @code
//!   linear_kth_par kp(adj);
//!   int kth_par = kp.kth_par(v, k);
//! @endcode
//! kth_par = a node k edges up from v
//! @time O(n + q)
//! @space O(n)
struct linear_kth_par {
  struct node {
    int d, p = -1, idx, dl;
    vector<int> lad;
  };
  vector<node> t;
  vector<pair<int, int>> j;
  linear_kth_par(const vector<vector<int>>& adj):
    t((int)size(adj)), j(2 * (int)size(t)) {
    vector<int> st;
    int pos = 1;
    auto add_j = [&]() -> void {
      j[pos] = {
        st[max(0, (int)size(st) - 1 - 2 * (pos & -pos))],
        st[max(0, (int)size(st) - 1 - 4 * (pos & -pos))]};
      pos++;
    };
    auto dfs = [&](auto&& self, int v) -> void {
      st.push_back(v);
      t[v].idx = pos, t[v].dl = v;
      add_j();
      for (int u : adj[v])
        if (u != t[v].p) {
          t[u].d = t[t[u].p = v].d + 1;
          self(self, u);
          if (t[t[u].dl].d > t[t[v].dl].d)
            t[v].dl = t[u].dl;
          add_j();
        }
      st.pop_back();
    };
    for (int i = 0; i < ((int)size(t)); i++) {
      if (t[i].p == -1) dfs(dfs, i);
      if (t[i].p == -1 || t[t[i].p].dl != t[i].dl) {
        int leaf = t[i].dl;
        vector<int>& lad = t[leaf].lad;
        lad.resize(
          min((t[leaf].d - t[i].d) * 2, t[leaf].d + 1),
          leaf);
        for (int k = 1; k < ((int)size(lad)); k++)
          lad[k] = t[lad[k - 1]].p;
      }
    }
  }
  int kth_par(int v, int k) {
    assert(0 <= k && k <= t[v].d);
    switch (k) {
    case 0: return v;
    case 1: return t[v].p;
    case 2: return t[t[v].p].p;
    default:
      int i = 1 << __lg(k / 3);
      auto [j1, j2] = j[(t[v].idx & -i) | i];
      int leaf = t[t[v].d - t[j2].d <= k ? j2 : j1].dl;
      return t[leaf].lad[k + t[leaf].d - t[v].d];
    }
  }
};
struct linear_kth_path {
  linear_lca lin_lca;
  linear_kth_par lin_kp;
  linear_kth_path(const vector<vector<int>>& adj):
    lin_lca(adj), lin_kp(adj) {}
  //! @param u,v endpoint nodes of path
  //! @param k index into path
  //! @returns the node
  //! vi({u,p[u],..,lca(u,v),..,p[v],v})[k], or -1, so u if
  //! k=0
  //! @time O(1)
  //! @space O(1)
  int kth_path(int u, int v, int k) {
    int lca_d = lin_kp.t[lin_lca.lca(u, v)].d;
    int u_lca = lin_kp.t[u].d - lca_d;
    int v_lca = lin_kp.t[v].d - lca_d;
    if (k <= u_lca) return lin_kp.kth_par(u, k);
    if (k <= u_lca + v_lca)
      return lin_kp.kth_par(v, u_lca + v_lca - k);
    return -1;
  }
};
