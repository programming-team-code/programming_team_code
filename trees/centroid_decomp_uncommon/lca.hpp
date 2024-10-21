//! @code
//!   centroid(adj, [&](const vector<vi>& adj,
//!     int cent) {
//!   });
//! @endcode
//! @time O(n log n)
//! @space O(n)
template<class F> struct centroid {
  vector<vector<int>> adj;
  F f;
  vector<int> sub_sz;
  centroid(const vector<vector<int>>& a_adj, F a_f):
    adj(a_adj), f(a_f), sub_sz(ssize(adj), -1) {
    for (int i = 0; i < ssize(adj); i++)
      if (sub_sz[i] == -1) dfs(i);
  }
  void calc_sz(int v, int p) {
    sub_sz[v] = 1;
    for (int u : adj[v])
      if (u != p) calc_sz(u, v), sub_sz[v] += sub_sz[u];
  }
  void dfs(int v) {
    calc_sz(v, -1);
    for (int p = -1, sz_root = sub_sz[v];;) {
      auto big_ch =
        find_if(begin(adj[v]), end(adj[v]), [&](int u) {
          return u != p && 2 * sub_sz[u] > sz_root;
        });
      if (big_ch == end(adj[v])) break;
      p = v, v = *big_ch;
    }
    f(adj, v);
    for (int u : adj[v]) {
      iter_swap(find(begin(adj[u]), end(adj[u]), v),
        rbegin(adj[u]));
      adj[u].pop_back();
      dfs(u);
    }
  }
};
//! https://codeforces.com/blog/entry/81661#comment-686024
struct cd_lca {
  vector<int> d;
  vector<vector<int>> mn_d, to_cent;
  int cmp(int u, int v) { return d[u] < d[v] ? u : v; }
  //! @param adj unrooted, undirected tree
  //! @time O(n log n)
  //! @space O(n log n) for `mn_d` and `to_cent` vectors
  cd_lca(const vector<vector<int>>& adj):
    d(ssize(adj)), mn_d(ssize(adj)), to_cent(ssize(adj)) {
    auto dfs_d = [&](auto&& self, int v, int p) -> void {
      for (int u : adj[v])
        if (u != p) d[u] = 1 + d[v], self(self, u, v);
    };
    dfs_d(dfs_d, 0, -1);
    centroid(adj,
      [&](const vector<vector<int>>& cd_adj, int cent) {
        auto dfs = [&](auto&& self, int v, int p) -> void {
          mn_d[v].push_back(
            p == -1 ? v : cmp(mn_d[p].back(), v));
          to_cent[v].push_back(cent);
          for (int u : cd_adj[v])
            if (u != p) self(self, u, v);
        };
        dfs(dfs, cent, -1);
      });
  }
  //! @param u,v nodes
  //! @returns lca of u, v; where the root is 0
  //! @time O(log(n))
  //! @space O(1)
  int lca(int u, int v) {
    for (int i = min(ssize(mn_d[u]), ssize(mn_d[v])) - 1;;
         i--)
      if (to_cent[u][i] == to_cent[v][i])
        return cmp(mn_d[u][i], mn_d[v][i]);
  }
};
