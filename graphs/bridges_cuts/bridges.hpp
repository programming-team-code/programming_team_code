/**
 * @see https://cp-algorithms.com/graph/bridge-searching.html
 * @code{.cpp}
       vector<vector<pii>> adj(n);
       rep (i, 0, m) {
           int u, v;
           cin >> u >> v;
           u--, v--;
           adj[u].emplace_back(v, i);
           adj[v].emplace_back(u, i);
       }
       auto [num_2_edge_ccs, is_bridge, two_edge_ccid] = bridges(adj, m);
 * @endcode
 */
struct bridges {
  int num_2_edge_ccs = 0; /**< number of components in bridge tree */
  vector<bool> is_bridge; /**< is_bridge[edge id] = 1 iff bridge edge */
  vector<int> two_edge_ccid; /**< two_edge_ccid[node] = id of 2 edge component (labeled 0, 1, ..., `num_2_edge_ccs`-1) */
  /**
   * @param adj undirected graph; possibly with multiple edges
   * @param m number of edges
   * @time O(n + m)
   * @space this allocates member vectors which are O(n + m)
   */
  bridges(const vector<vector<pair<int, int>>>& adj, int m) : is_bridge(m), two_edge_ccid((int)size(adj), -1) {
    int n = (int)size(adj), timer = 1;
    vector<int> tin(n), st;
    auto dfs = [&](auto&& self, int u, int p_id) -> int {
      int low = tin[u] = timer++, siz = (int)size(st);
      st.push_back(u);
      for (auto [v, e_id] : adj[u]) {
        if (e_id == p_id) continue;
        if (!tin[v]) low = min(low, self(self, v, e_id));
        low = min(low, tin[v]);
      }
      if (tin[u] == low) {
        if (p_id != -1) is_bridge[p_id] = 1;
        for (int i = siz; i < ((int)size(st)); i++)
          two_edge_ccid[st[i]] = num_2_edge_ccs;
        st.resize(siz);
        num_2_edge_ccs++;
      }
      return low;
    };
    for (int i = 0; i < (n); i++)
      if (!tin[i]) dfs(dfs, i, -1);
  }
};
