#pragma once
//! https://cp-algorithms.com/graph/bridge-searching.html
//! @code
//!   vector<vector<pii>> adj(n);
//!   rep (i, 0, m) {
//!     int u, v;
//!     cin >> u >> v;
//!     u--, v--;
//!     adj[u].emplace_back(v, i);
//!     adj[v].emplace_back(u, i);
//!   }
//!   auto [num_ccs, is_bridge, br_id] = bridges(adj, m);
//! @endcode
//! is_bridge[edge id] = 1 iff bridge edge
//! br_id[v] = id, 0<=id<num_ccs
//! @time O(n + m)
//! @space O(n + m)
struct bridges {
  int num_ccs = 0;
  vector<bool> is_bridge;
  vi br_id;
  bridges(const vector<vector<pii>>& adj, int m):
    is_bridge(m), br_id(sz(adj), -1) {
    int n = sz(adj), timer = 1;
    vi tin(n), st;
    auto dfs = [&](auto&& self, int v, int p_id) -> int {
      int low = tin[v] = timer++, siz = sz(st);
      st.push_back(v);
      for (auto [u, e_id] : adj[v]) {
        if (e_id == p_id) continue;
        if (!tin[u]) low = min(low, self(self, u, e_id));
        low = min(low, tin[u]);
      }
      if (tin[v] == low) {
        if (p_id != -1) is_bridge[p_id] = 1;
        rep(i, siz, sz(st)) br_id[st[i]] = num_ccs;
        st.resize(siz);
        num_ccs++;
      }
      return low;
    };
    rep(i, 0, n) if (!tin[i]) dfs(dfs, i, -1);
  }
};
