/**
 * @code{.cpp}
       centroid(adj, [&](const vector<vector<int>>& adj, int cent) {
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
      : adj(a_adj), f(a_f), sub_sz(ssize(adj), -1) {
    for (int i = 0; i < ssize(adj); i++)
      if (sub_sz[i] == -1) dfs(i);
  }
  void calc_sz(int u, int p) {
    sub_sz[u] = 1;
    for (int v : adj[u])
      if (v != p)
        calc_sz(v, u), sub_sz[u] += sub_sz[v];
  }
  void dfs(int u) {
    calc_sz(u, -1);
    for (int p = -1, sz_root = sub_sz[u];;) {
      auto big_ch = find_if(begin(adj[u]), end(adj[u]), [&](int v) {
        return v != p && 2 * sub_sz[v] > sz_root;
      });
      if (big_ch == end(adj[u])) break;
      p = u, u = *big_ch;
    }
    f(adj, u);
    for (int v : adj[u]) {
      iter_swap(find(begin(adj[v]), end(adj[v]), u), rbegin(adj[v]));
      adj[v].pop_back();
      dfs(v);
    }
  }
};
/**
 * @param adj unrooted, connected forest
 * @param k number of edges
 * @returns array `num_paths` where `num_paths[i]` = number of paths with k
 * edges where node `i` is on the path. 0-based nodes.
 * @time O(n log n)
 * @space this function allocates/returns various vectors which are all O(n)
 */
vector<int64_t> count_paths_per_node(const vector<vector<int>>& adj, int k) {
  vector<int64_t> num_paths(ssize(adj));
  centroid(adj, [&](const vector<vector<int>>& cd_adj, int cent) {
    vector pre_d{1}, cur_d{0};
    auto dfs = [&](auto&& self, int u, int p, int d) {
      if (d > k) return 0LL;
      if (ssize(cur_d) <= d) cur_d.push_back(0);
      cur_d[d]++;
      auto cnt = 0LL;
      if (k - d < ssize(pre_d)) cnt += pre_d[k - d];
      for (int v : cd_adj[u])
        if (v != p)
          cnt += self(self, v, u, d + 1);
      num_paths[u] += cnt;
      return cnt;
    };
    auto dfs_child = [&](int child) {
      auto cnt = dfs(dfs, child, cent, 1);
      pre_d.resize(ssize(cur_d));
      for (int i = 1; i < ssize(cur_d) && cur_d[i]; i++)
        pre_d[i] += cur_d[i], cur_d[i] = 0;
      return cnt;
    };
    for (int child : cd_adj[cent])
      num_paths[cent] += dfs_child(child);
    pre_d = cur_d = {0};
    for_each(rbegin(cd_adj[cent]), rend(cd_adj[cent]), dfs_child);
  });
  return num_paths;
}
