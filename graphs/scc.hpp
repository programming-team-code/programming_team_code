//! https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/SCC.h
//! @code
//!   vector<basic_string<int>> adj(n);
//!   auto [num_sccs, scc_id] = scc(adj);
//! @endcode
//! scc_id[u] = id, 0<=id<num_sccs
//! for each edge u -> v: scc_id[u] >= scc_id[v]
//! @time O(n + m)
//! @space O(n)
auto scc(const auto& adj) {
  int n = ssize(adj), num_sccs = 0, q = 0, s = 0;
  vector<int> scc_id(n, -1), tin(n), st(n);
  auto dfs = [&](auto&& self, int u) -> int {
    int low = tin[u] = ++q;
    st[s++] = u;
    for (int v : adj[u])
      if (scc_id[v] < 0)
        low = min(low, tin[v] ?: self(self, v));
    if (tin[u] == low) {
      while (scc_id[u] < 0) scc_id[st[--s]] = num_sccs;
      num_sccs++;
    }
    return low;
  };
  for (int i = 0; i < n; i++)
    if (!tin[i]) dfs(dfs, i);
  return pair{num_sccs, scc_id};
}
