//! https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/SCC.h
//! @code
//!   auto [num_sccs, scc_id] = sccs(adj);
//! @endcode
//! scc_id[v] = id, 0<=id<num_sccs
//! for each edge u -> v: scc_id[u] >= scc_id[v]
//! @time O(n + m)
//! @space O(n)
struct sccs {
  int num_sccs = 0;
  vector<int> scc_id;
  sccs(const vector<vector<int>>& adj):
    scc_id(ssize(adj), -1) {
    int n = ssize(adj), timer = 1;
    vector<int> tin(n), st;
    auto dfs = [&](auto&& self, int v) -> int {
      int low = tin[v] = timer++, siz = ssize(st);
      st.push_back(v);
      for (int u : adj[v])
        if (scc_id[u] < 0)
          low = min(low, tin[u] ? tin[u] : self(self, u));
      if (tin[v] == low) {
        for (int i = siz; i < ssize(st); i++)
          scc_id[st[i]] = num_sccs;
        st.resize(siz);
        num_sccs++;
      }
      return low;
    };
    for (int i = 0; i < n; i++)
      if (!tin[i]) dfs(dfs, i);
  }
};
