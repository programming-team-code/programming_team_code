//! https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/SCC.h
//! @code
//!   vector<basic_string<int>> adj(n);
//!   auto [num_sccs, scc_id] = sccs(adj);
//! @endcode
//! scc_id[v] = id, 0<=id<num_sccs
//! for each edge u -> v: scc_id[u] >= scc_id[v]
//! @time O(n + m)
//! @space O(n)
auto sccs(const auto& adj) {
  int n = ssize(adj), num_sccs = 0, q = 0, s = 0;
  vector<int> scc_id(n, -1), tin(n), st(n);
  auto dfs = [&](auto&& self, int v) -> int {
    int low = tin[v] = ++q;
    st[s++] = v;
    for (int u : adj[v])
      if (scc_id[u] < 0)
        low = min(low, tin[u] ?: self(self, u));
    if (tin[v] == low) {
      while (scc_id[v] < 0) scc_id[st[--s]] = num_sccs;
      num_sccs++;
    }
    return low;
  };
  for (int i = 0; i < n; i++)
    if (!tin[i]) dfs(dfs, i);
  return pair{num_sccs, scc_id};
}
