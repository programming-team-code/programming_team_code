#pragma once
//! https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/SCC.h
//! @code
//!   auto [num_sccs, scc_id] = sccs(adj);
//! @endcode
//! scc_id[v] = id, 0<=id<num_sccs
//! for each edge u -> v: scc_id[u] >= scc_id[v]
//! @time O(n + m)
//! @space O(n)
pair<int, vector<int>> sccs(const vector<vector<int>>& adj) {
  int num_sccs = 0, n = ssize(adj), timer = 0;
  vector<int> scc_id(n, -1), tin(n), low(n), st, e(n), p(n, -1);
  for (int i = 0; i < n; i++)
    if (!tin[i]) {
      int v = i;
      while (v >= 0) {
        if (e[v]) {
          int u = adj[v][e[v] - 1];
          if (scc_id[u] == -1) low[v] = min(low[v], low[u]);
        } else {
          low[v] = tin[v] = ++timer;
          st.push_back(v);
        }
        if (e[v] < ssize(adj[v])) {
          int u = adj[v][e[v]++];
          if (!tin[u]) p[u] = v, v = u;
        } else {
          if (low[v] == tin[v]) {
            while (scc_id[v] == -1) {
              scc_id[st.back()] = num_sccs;
              st.pop_back();
            }
            num_sccs++;
          }
          v = p[v];
        }
      }
    }
  return {num_sccs, scc_id};
}
