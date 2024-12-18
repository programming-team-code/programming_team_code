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
