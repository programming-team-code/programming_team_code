/**
 * @see https://cp-algorithms.com/graph/bridge-searching.html
 * @code{.cpp}
       vector<vector<array<int, 2>>> adj(n);
       for (int i = 0; i < m; i++) {
           int u, v;
           cin >> u >> v;
           u--, v--;
           adj[u].push_back({v, i});
           adj[v].push_back({u, i});
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
  bridges(const vector<vector<array<int, 2>>>& adj, int m) : is_bridge(m), two_edge_ccid(ssize(adj), -1) {
    int n = ssize(adj), timer = 1;
    vector<int> tin(n), st;
    auto dfs = [&](auto&& self, int u, int p_id) -> int {
      int low = tin[u] = timer++, siz = ssize(st);
      st.push_back(u);
      for (auto [v, e_id] : adj[u]) {
        if (e_id == p_id) continue;
        if (!tin[v]) low = min(low, self(self, v, e_id));
        low = min(low, tin[v]);
      }
      if (tin[u] == low) {
        if (p_id != -1) is_bridge[p_id] = 1;
        for (int i = siz; i < ssize(st); i++)
          two_edge_ccid[st[i]] = num_2_edge_ccs;
        st.resize(siz);
        num_2_edge_ccs++;
      }
      return low;
    };
    for (int i = 0; i < n; i++)
      if (!tin[i]) dfs(dfs, i, -1);
  }
};
/**
 * Never adds multiple edges as bridges.hpp correctly marks them as
 * non-bridges.
 * @code{.cpp}
       bridges cc(adj, m);
       vector<vector<int>> bt = bridge_tree(adj, cc);
 * @endcode
 * @param adj undirected graph
 * @param cc what's calculated by bridges
 * @returns adjacency list of bridge tree
 * @time O(n + m)
 * @space besides the O(n + m) sized params, this function allocates and
 * returns `tree` vector, which is O(n)
 */
vector<vector<int>> bridge_tree(const vector<vector<array<int, 2>>>& adj, const bridges& cc) {
  vector<vector<int>> tree(cc.num_2_edge_ccs);
  for (int i = 0; i < ssize(adj); i++)
    for (auto [u, e_id] : adj[i])
      if (cc.is_bridge[e_id])
        tree[cc.two_edge_ccid[i]].push_back(cc.two_edge_ccid[u]);
  return tree;
}
