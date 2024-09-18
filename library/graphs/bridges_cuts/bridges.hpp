#pragma once
//! https://cp-algorithms.com/graph/bridge-searching.html
//! @code
//!     vector<vector<pii>> adj(n);
//!     rep (i, 0, m) {
//!         int u, v;
//!         cin >> u >> v;
//!         u--, v--;
//!         adj[u].emplace_back(v, i);
//!         adj[v].emplace_back(u, i);
//!     }
//!     auto [num_2_edge_ccs, is_bridge, two_edge_ccid] =
//!     bridges(adj, m);
//! @endcode
struct bridges {
  int num_2_edge_ccs =
    0; //!< number of components in bridge tree
  vector<bool>
    is_bridge; //!< is_bridge[edge id] = 1 iff bridge edge
  vi two_edge_ccid; //!< two_edge_ccid[node] = id of 2 edge
                    //!< component (labeled 0, 1, ...,
                    //!< `num_2_edge_ccs`-1)
  //! @param adj undirected graph; possibly with multiple
  //! edges
  //! @param m number of edges
  //! @time O(n + m)
  //! @space this allocates member vectors which are O(n + m)
  bridges(const vector<vector<pii>>& adj, int m):
    is_bridge(m), two_edge_ccid(sz(adj), -1) {
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
        rep(i, siz, sz(st)) two_edge_ccid[st[i]] =
          num_2_edge_ccs;
        st.resize(siz);
        num_2_edge_ccs++;
      }
      return low;
    };
    rep(i, 0, n) if (!tin[i]) dfs(dfs, i, -1);
  }
};
