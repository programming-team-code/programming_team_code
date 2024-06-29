/**
 * @see https://github.com/kth-competitive-programming /kactl/blob/main/content/graph/SCC.h
 * @code{.cpp}
       auto [num_sccs, scc_id] = sccs(adj);
 * @endcode
 */
struct sccs {
  int num_sccs = 0; /**< number of SCCs */
  /**
   * scc_id[u] = id of SCC containing node u. It satisfies:
   * - 0 <= scc_id[u] < num_sccs
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
    st.reserve(n);
    auto dfs = [&](auto&& self, int u) -> int {
      int low = tin[u] = timer++, siz = (int)size(st);
      st.push_back(u);
      for (int v : adj[u])
        if (scc_id[v] < 0)
          low = min(low, tin[v] ? tin[v] : self(self, v));
      if (tin[u] == low) {
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
 * @see [Radecki Algorithm!](https://codeforces.com/blog/entry/91608)
 *
 * @note does not support self loops (e.a. edges of the form {u, u})
 *
 * @param edge_updates directed edges {u, v} where u -> v
 * @param n number of vertices
 *
 * @returns a vec joins where joins[i] = minimum prefix of edges [0, joins[i]]
 * for eds[i][0] and eds[i][1] to be in the same SCC; iff eds[i][0] and
 * eds[i][1] are never in the same SCC then joins[i] = m
 *
 * @time O((n + m) log m)
 * @space O(n + m)
 */
vector<int> offline_incremental_scc(vector<array<int, 2>> edge_updates, int n) {
  int m = (int)size(edge_updates);
  vector<int> ids(n, -1), joins(m, m);
  vector<array<int, 3>> eds(m);
  for (int t = 0; t < (m); t++) {
    auto [u, v] = edge_updates[t];
    assert(u != v);
    eds[t] = {u, v, t};
  }
  auto divide_and_conquer = [&](auto&& self, auto el, auto er, int tl, int tr) {
    int mid = (tl + tr) / 2;
    vector<int> vs;
    vector<vector<int>> adj;
    for (auto it = el; it != er; it++) {
      auto& [u, v, t] = *it;
      for (int w : {u, v}) {
        if (ids[w] != -1) continue;
        ids[w] = (int)size(vs);
        vs.push_back(w);
        adj.emplace_back();
      }
      u = ids[u], v = ids[v];
      if (t <= mid) adj[u].push_back(v);
    }
    for (int v : vs) ids[v] = -1;
    auto scc_id = sccs(adj).scc_id;
    auto split = partition(
        el, er, [&](const auto& ed) { return scc_id[ed[0]] == scc_id[ed[1]]; });
    for (auto it = el; it != split; it++) {
      int t = it->back();
      joins[t] = min(joins[t], mid);
    }
    if (tr - tl == 1) return;
    for (auto it = split; it != er; it++) {
      auto& [u, v, t] = *it;
      u = scc_id[u], v = scc_id[v];
    }
    // deallocate to avoid O(m log m) memory
    vector<int>().swap(vs);
    vector<vector<int>>().swap(adj);
    vector<int>().swap(scc_id);
    self(self, el, split, tl, mid);
    self(self, split, er, mid, tr);
  };
  divide_and_conquer(divide_and_conquer, begin(eds), end(eds), 0, m);
  return joins;
}
