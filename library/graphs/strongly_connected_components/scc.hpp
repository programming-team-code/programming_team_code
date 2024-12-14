#pragma once
//! https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/SCC.h
//! @code
//!   vector<vi> adj(n);
//!   auto [num_sccs, scc_id] = sccs(adj);
//! @endcode
//! scc_id[v] = id, 0<=id<num_sccs
//! for each edge u -> v: scc_id[u] >= scc_id[v]
//! @time O(n + m)
//! @space O(n)
struct sccs {
  int num_sccs = 0;
  vi scc_id;
  sccs(const vector<vi>& adj): scc_id(sz(adj), -1) {
    int n = sz(adj), timer = 1;
    vi tin(n), st;
    auto dfs = [&](auto&& self, int v) -> int {
      int low = tin[v] = timer++, siz = sz(st);
      st.push_back(v);
      for (int u : adj[v])
        if (scc_id[u] < 0)
          low = min(low, tin[u] ? tin[u] : self(self, u));
      if (tin[v] == low) {
        rep(i, siz, sz(st)) scc_id[st[i]] = num_sccs;
        st.resize(siz);
        num_sccs++;
      }
      return low;
    };
    rep(i, 0, n) if (!tin[i]) dfs(dfs, i);
  }
};
