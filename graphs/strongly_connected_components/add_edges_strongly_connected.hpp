/**
 * @see https://github.com/kth-competitive-programming /kactl/blob/main/content/graph/SCC.h
 * @code{.cpp}
       auto [num_sccs, scc_id] = sccs(adj);
 * @endcode
 */
struct sccs {
  int num_sccs = 0; /**< number of SCCs */
  /**
   * scc_id[v] = id of SCC containing node v. It satisfies:
   * - 0 <= scc_id[v] < num_sccs
   * - for each edge u -> v: scc_id[u] >= scc_id[v]
   */
  vector<int> scc_id;
  /**
   * @param adj directed, unweighted graph
   * @time O(n + m)
   * @space this allocates member `scc_id` which is O(n)
   */
  sccs(const vector<vector<int>>& adj) : scc_id((int)size(adj), -1) {
    int n = (int)size(adj), timer = 1;
    vector<int> tin(n), st;
    auto dfs = [&](auto&& self, int v) -> int {
      int low = tin[v] = timer++, siz = (int)size(st);
      st.push_back(v);
      for (int u : adj[v])
        if (scc_id[u] < 0)
          low = min(low, tin[u] ? tin[u] : self(self, u));
      if (tin[v] == low) {
        for (int i = siz; i < ((int)size(st)); i++)
          scc_id[st[i]] = num_sccs;
        st.resize(siz);
        num_sccs++;
      }
      return low;
    };
    for (int i = 0; i < (n); i++)
      if (!tin[i]) dfs(dfs, i);
  }
};
/**
 * @see https://codeforces.com/blog/entry/15102
 *
 * Add minimum extra directed edges to directed graph to make it strongly connected.
 * If the directed graph is not initially strongly connected, then the edge
 * list's size is max(# zero indegree SCCs, # zero outdegree SCCs)
 *
 * @code{.cpp}
       auto [num_sccs, scc_id] = sccs(adj);
       vector<pii> edges = extra_edges(adj, num_sccs, scc_id);
 * @endcode
 * @param adj,num_sccs,scc_id directed graph and its SCCs
 * @returns directed edge list: edges[i][0] -> edges[i][1]
 * @time O(n + m)
 * @space An O(n) edge list is allocated and returned, but multiple O(n + m)
 * vectors are allocated temporarily
 */
vector<pair<int, int>> extra_edges(const vector<vector<int>>& adj, int num_sccs, const vector<int>& scc_id) {
  if (num_sccs == 1) return {};
  int n = (int)size(adj);
  vector<vector<int>> scc_adj(num_sccs);
  vector<bool> zero_in(num_sccs, 1);
  for (int i = 0; i < (n); i++)
    for (int u : adj[i]) {
      if (scc_id[i] == scc_id[u]) continue;
      scc_adj[scc_id[i]].push_back(scc_id[u]);
      zero_in[scc_id[u]] = 0;
    }
  vector<bool> vis(num_sccs);
  auto dfs = [&](auto&& self, int v) {
    if (empty(scc_adj[v])) return v;
    for (int u : scc_adj[v])
      if (!vis[u]) {
        vis[u] = 1;
        int zero_out = self(self, u);
        if (zero_out != -1) return zero_out;
      }
    return -1;
  };
  vector<pair<int, int>> edges;
  vector<int> in_unused;
  for (int i = 0; i < (num_sccs); i++)
    if (zero_in[i]) {
      vis[i] = 1;
      int zero_out = dfs(dfs, i);
      if (zero_out != -1) edges.emplace_back(zero_out, i);
      else in_unused.push_back(i);
    }
  for (int i = 1; i < ((int)size(edges)); i++) swap(edges[i].first, edges[i - 1].first);
  for (int i = 0; i < (num_sccs); i++)
    if (empty(scc_adj[i]) && !vis[i]) {
      if (!empty(in_unused)) {
        edges.emplace_back(i, in_unused.back());
        in_unused.pop_back();
      } else edges.emplace_back(i, num_sccs - 1);
    }
  for (int v : in_unused) edges.emplace_back(0, v);
  vector<int> to_node(num_sccs);
  for (int i = 0; i < (n); i++) to_node[scc_id[i]] = i;
  for (auto& [u, v] : edges) u = to_node[u], v = to_node[v];
  return edges;
}
