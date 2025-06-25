//! https://codeforces.com/blog/entry/125371
//! @code
//!   {
//!     vector<vi> adj(n);
//!     linear_lca llca(adj);
//!   }
//!   vector<basic_string<int>> adj(n);
//!   linear_lca llca(adj);
//! @endcode
//! @time O(n + q)
//! @space O(n)
struct linear_lca {
  struct node {
    int d, label, asc;
  };
  vector<node> t;
  vector<int> head;
  linear_lca(const auto& adj):
    t(ssize(adj)), head(ssize(t) + 1) {
    vector<pair<int, int>> order;
    auto dfs = [&](auto&& self, int v, int p) -> void {
      order.emplace_back(v, p);
      t[v].label = ssize(order);
      for (int u : adj[v])
        if (u != p) {
          t[u].d = 1 + t[v].d;
          self(self, u, v);
          head[t[u].label] = v;
          if ((t[u].label & -t[u].label) >
            (t[v].label & -t[v].label))
            t[v].label = t[u].label;
        }
    };
    for (int i = 0; i < ssize(t); i++)
      if (t[i].d == 0) dfs(dfs, i, i);
    for (auto [v, p] : order)
      t[v].asc = t[p].asc | (t[v].label & -t[v].label);
  }
  int lca(int u, int v) {
    if (unsigned j = t[u].label ^ t[v].label; j) {
      j = t[u].asc & t[v].asc & -bit_floor(j);
      if (unsigned k = t[u].asc ^ j; k)
        k = bit_floor(k), u = head[(t[u].label & -k) | k];
      if (unsigned k = t[v].asc ^ j; k)
        k = bit_floor(k), v = head[(t[v].label & -k) | k];
    }
    return t[u].d < t[v].d ? u : v;
  }
  int dist_edges(int u, int v) {
    return t[u].d + t[v].d - 2 * t[lca(u, v)].d;
  }
};
//! https://codeforces.com/blog/entry/126580
//! @code
//!   {
//!     vector<vi> adj(n);
//!     linear_kth_par kp(adj);
//!   }
//!   vector<basic_string<int>> adj(n);
//!   linear_kth_par kp(adj);
//!   int kth_par = kp.kth_par(v, k);
//! @endcode
//! kth_par = a node k edges up from v
//! @time O(n + q)
//! @space O(n)
struct linear_kth_par {
  struct node {
    int d, p = -1, dl, idx_j;
    basic_string<int> lad;
  };
  vector<node> t;
  vector<pair<int, int>> j;
  linear_kth_par(const auto& adj):
    t(ssize(adj)), j(2 * ssize(t)) {
    vector<int> st;
    int pos = 1;
    auto add_j = [&]() -> void {
      j[pos] = {
        st[max<int>(0, ssize(st) - 1 - 2 * (pos & -pos))],
        st[max<int>(0, ssize(st) - 1 - 4 * (pos & -pos))]};
      pos++;
    };
    auto dfs = [&](auto&& self, int v) -> void {
      st.push_back(v);
      t[v].idx_j = pos, t[v].dl = v;
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
    for (int i = 0; i < ssize(t); i++) {
      if (t[i].p == -1) dfs(dfs, i);
      if (t[i].p == -1 || t[t[i].p].dl != t[i].dl) {
        int v = t[i].dl, len = (t[v].d - t[i].d) * 2;
        auto& lad = t[v].lad;
        for (; v != -1 && len--; v = t[v].p) lad += v;
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
      int i = bit_floor(unsigned(k / 3));
      auto [j1, j2] = j[(t[v].idx_j & -i) | i];
      int leaf = t[t[v].d - t[j2].d <= k ? j2 : j1].dl;
      return t[leaf].lad[k + t[leaf].d - t[v].d];
    }
  }
};
struct linear_kth_path {
  linear_lca lin_lca;
  linear_kth_par lin_kp;
  linear_kth_path(const auto& adj):
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
