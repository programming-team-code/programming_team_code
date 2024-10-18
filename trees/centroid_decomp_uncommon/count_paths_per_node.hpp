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
    adj(a_adj), f(a_f), sub_sz((int)size(adj), -1) {
    for (int i = 0; i < ((int)size(adj)); i++)
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
//! @param adj unrooted, connected forest
//! @param k number of edges
//! @returns array `num_paths` where `num_paths[i]` =
//! number of paths with k edges where node `i` is on the
//! path. 0-based nodes.
//! @time O(n log n)
//! @space this function allocates/returns various vectors
//! which are all O(n)
vector<int64_t> count_paths_per_node(
  const vector<vector<int>>& adj, int k) {
  vector<int64_t> num_paths((int)size(adj));
  centroid(adj,
    [&](const vector<vector<int>>& cd_adj, int cent) {
      vector pre_d{1}, cur_d{0};
      auto dfs = [&](auto&& self, int v, int p,
                   int d) -> int64_t {
        if (d > k) return 0LL;
        if ((int)size(cur_d) <= d) cur_d.push_back(0);
        cur_d[d]++;
        int64_t cnt = 0;
        if (k - d < (int)size(pre_d)) cnt += pre_d[k - d];
        for (int u : cd_adj[v])
          if (u != p) cnt += self(self, u, v, d + 1);
        num_paths[v] += cnt;
        return cnt;
      };
      auto dfs_child = [&](int child) -> int64_t {
        int64_t cnt = dfs(dfs, child, cent, 1);
        pre_d.resize((int)size(cur_d));
        for (int i = 1; i < (int)size(cur_d) && cur_d[i];
             i++)
          pre_d[i] += cur_d[i], cur_d[i] = 0;
        return cnt;
      };
      for (int child : cd_adj[cent])
        num_paths[cent] += dfs_child(child);
      pre_d = cur_d = {0};
      for_each(rbegin(cd_adj[cent]), rend(cd_adj[cent]),
        dfs_child);
    });
  return num_paths;
}
