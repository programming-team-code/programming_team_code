//! @code
//!   centroid(adj, [&](const vector<vi>& adj,
//!     int cent, int par_cent) {
//!   });
//! @endcode
//! @time O(n log n)
//! @space O(n)
template<class F> struct centroid {
  vector<vector<int>> adj;
  F f;
  vector<int> siz;
  centroid(const vector<vector<int>>& adj, F f):
    adj(adj), f(f), siz(ssize(adj), -1) {
    for (int i = 0; i < ssize(adj); i++)
      if (siz[i] == -1) dfs(i, -1);
  }
  void calc_sz(int v, int p) {
    siz[v] = 1;
    for (int u : adj[v])
      if (u != p) calc_sz(u, v), siz[v] += siz[u];
  }
  void dfs(int v, int p) {
    calc_sz(v, -1);
    for (int w = -1, sz_root = siz[v];;) {
      auto big_ch = ranges::find_if(adj[v], [&](int u) {
        return u != w && 2 * siz[u] > sz_root;
      });
      if (big_ch == end(adj[v])) break;
      w = v, v = *big_ch;
    }
    f(adj, v, p);
    for (int u : adj[v]) {
      iter_swap(ranges::find(adj[u], v), rbegin(adj[u]));
      adj[u].pop_back();
      dfs(u, v);
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
      [&](const vector<vector<int>>& cd_adj, int cent,
        int) {
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
