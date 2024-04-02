/** @file */
#pragma once
/**
 * @see https://cp-algorithms.com/graph/bridge-searching.html
 * @code{.cpp}
       vector<vector<pii>> adj(n);
       rep (i, 0, m) {
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
  vi two_edge_ccid; /**< two_edge_ccid[node] = id of 2 edge component (labeled 0, 1, ..., `num_2_edge_ccs`-1) */
  /**
   * @param adj undirected graph; possibly with multiple edges
   * @param m number of edges
   * @time O(n + m)
   * @space this allocates member vectors which are O(n + m)
   */
  bridges(const vector<vector<pii>>& adj, int m) : is_bridge(m), two_edge_ccid(sz(adj), -1) {
    int n = sz(adj), timer = 1;
    vi tin(n), st;
    auto dfs = [&](auto&& self, int u, int p_id) -> int {
      int low = tin[u] = timer++, siz = sz(st);
      st.push_back(u);
      for (auto [v, e_id] : adj[u]) {
        if (e_id == p_id) continue;
        if (!tin[v]) low = min(low, self(self, v, e_id));
        low = min(low, tin[v]);
      }
      if (tin[u] == low) {
        if (p_id != -1) is_bridge[p_id] = 1;
        rep (i, siz, sz(st))
          two_edge_ccid[st[i]] = num_2_edge_ccs;
        st.resize(siz);
        num_2_edge_ccs++;
      }
      return low;
    };
    rep (i, 0, n)
      if (!tin[i]) dfs(dfs, i, -1);
  }
};
