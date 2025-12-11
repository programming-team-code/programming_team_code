//! @code
//!   vector<basic_string<int>> adj(n);
//!   centroid(adj, [&](const auto& adj,
//!     int cent, int par_cent) {});
//! @endcode
//! @time O(n log n)
//! @space O(n)
template<class F, class G> struct centroid {
  G adj;
  F f;
  vector<int> siz;
  centroid(const G& adj, F f):
    adj(adj), f(f), siz(ssize(adj), -1) {
    dfs(0, -1);
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
  vector<int64_t> num_paths(ssize(adj));
  centroid(adj,
    [&](const vector<vector<int>>& cd_adj, int cent, int) {
      vector pre_d{1}, cur_d{0};
      auto dfs = [&](auto&& self, int u, int p,
                   int d) -> int64_t {
        if (d > k) return 0LL;
        if (ssize(cur_d) <= d) cur_d.push_back(0);
        cur_d[d]++;
        int64_t cnt = 0;
        if (k - d < ssize(pre_d)) cnt += pre_d[k - d];
        for (int c : cd_adj[u])
          if (c != p) cnt += self(self, c, u, d + 1);
        num_paths[u] += cnt;
        return cnt;
      };
      auto dfs_child = [&](int child) -> int64_t {
        int64_t cnt = dfs(dfs, child, cent, 1);
        pre_d.resize(ssize(cur_d));
        for (int i = 1; i < ssize(cur_d) && cur_d[i]; i++)
          pre_d[i] += cur_d[i], cur_d[i] = 0;
        return cnt;
      };
      for (int child : cd_adj[cent])
        num_paths[cent] += dfs_child(child);
      pre_d = cur_d = {0};
      for (int child : cd_adj[cent] | views::reverse)
        dfs_child(child);
    });
  return num_paths;
}
