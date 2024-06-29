/**
 * @see https://cp-algorithms.com/graph/cutpoints.html
 * @code{.cpp}
       vector<vector<pii>> adj(n);
       rep (i, 0, m) {
           int u, v;
           cin >> u >> v;
           u--, v--;
           adj[u].emplace_back(v, i);
           adj[v].emplace_back(u, i);
       }
       auto [num_bccs, is_cut, bcc_id] = cuts(adj, m);
 * @endcode
 */
struct cuts {
  int num_bccs = 0; /**< number of bi-connected components */
  vector<bool> is_cut; /**< is_cut[node] = 1 iff cut node */
  vector<int> bcc_id; /**< bcc_id[edge id] = id of bcc (which are labeled 0, 1, ..., `num_bccs`-1) */
  /**
   * @param adj undirected graph; possibly with multiple edges; self edges not allowed
   * @param m number of edges
   * @time O(n + m)
   * @space this allocates member vectors which are O(n + m)
   */
  cuts(const vector<vector<pair<int, int>>>& adj, int m) : is_cut((int)size(adj)), bcc_id(m, -1) {
    int n = (int)size(adj), timer = 1;
    vector<int> tin(n), st;
    auto dfs = [&](auto&& self, int u, int p_id) -> int {
      int low = tin[u] = timer++, deg = 0;
      for (auto [v, e_id] : adj[u]) {
        assert(u != v);
        if (e_id == p_id) continue;
        if (!tin[v]) {
          int siz = (int)size(st);
          st.push_back(e_id);
          int low_ch = self(self, v, e_id);
          if (low_ch >= tin[u]) {
            is_cut[u] = 1;
            for (int i = siz; i < ((int)size(st)); i++)
              bcc_id[st[i]] = num_bccs;
            st.resize(siz);
            num_bccs++;
          }
          low = min(low, low_ch);
          deg++;
        } else if (tin[v] < tin[u]) {
          st.push_back(e_id);
          low = min(low, tin[v]);
        }
      }
      if (p_id == -1) is_cut[u] = (deg > 1);
      return low;
    };
    for (int i = 0; i < (n); i++)
      if (!tin[i]) dfs(dfs, i, -1);
  }
};
/**
 * @code{.cpp}
       cuts cc(adj, m);
       vector<vi> bvt = block_vertex_tree(adj, cc);
       //to loop over each unique bcc containing a node u:
       for (int bccid : bvt[u]) {
           bccid -= n;
       }
       //to loop over each unique node inside a bcc:
       for (int u : bvt[bccid + n]) {}
 * @endcode
 *
 * [0, n) are original nodes
 * [n, n + num_bccs) are BCC nodes
 *
 * @param adj undirected graph
 * @param cc what's calculated by cuts
 * @returns adjacency list of block vertex tree
 * @time O(n + m)
 * @space besides the O(n + m) sized params, this function allocates and
 * returns `bvt` vector which is O(n)
 */
vector<vector<int>> block_vertex_tree(const vector<vector<pair<int, int>>>& adj, const cuts& cc) {
  int n = (int)size(adj);
  vector<vector<int>> bvt(n + cc.num_bccs);
  vector<bool> vis(cc.num_bccs);
  for (int i = 0; i < (n); i++) {
    for (auto [_, e_id] : adj[i]) {
      int bccid = cc.bcc_id[e_id];
      if (!vis[bccid]) {
        vis[bccid] = 1;
        bvt[i].push_back(bccid + n);
        bvt[bccid + n].push_back(i);
      }
    }
    for (int bccid : bvt[i]) vis[bccid - n] = 0;
  }
  return bvt;
}
