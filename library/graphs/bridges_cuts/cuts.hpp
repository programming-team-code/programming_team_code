#pragma once
//! @see https://cp-algorithms.com/graph/cutpoints.html
//! @code{.cpp}
//!     vector<vector<pii>> adj(n);
//!     rep (i, 0, m) {
//!         int u, v;
//!         cin >> u >> v;
//!         u--, v--;
//!         adj[u].emplace_back(v, i);
//!         adj[v].emplace_back(u, i);
//!     }
//!     auto [num_bccs, is_cut, bcc_id] = cuts(adj, m);
//! @endcode
struct cuts {
  int num_bccs = 0; //!< number of bi-connected components
  vector<bool> is_cut; //!< is_cut[node] = 1 iff cut node
  vi
    bcc_id; //!< bcc_id[edge id] = id of bcc (which are labeled 0, 1, ..., `num_bccs`-1)
  //! @param adj undirected graph; possibly with multiple edges; self edges not allowed
  //! @param m number of edges
  //! @time O(n + m)
  //! @space this allocates member vectors which are O(n + m)
  cuts(const vector<vector<pii>>& adj, int m):
    is_cut(sz(adj)), bcc_id(m, -1) {
    int n = sz(adj), timer = 1;
    vi tin(n), st;
    auto dfs = [&](auto&& self, int v, int p_id) -> int {
      int low = tin[v] = timer++, deg = 0;
      for (auto [u, e_id] : adj[v]) {
        assert(v != u);
        if (e_id == p_id) continue;
        if (!tin[u]) {
          int siz = sz(st);
          st.push_back(e_id);
          int low_ch = self(self, u, e_id);
          if (low_ch >= tin[v]) {
            is_cut[v] = 1;
            rep(i, siz, sz(st)) bcc_id[st[i]] = num_bccs;
            st.resize(siz);
            num_bccs++;
          }
          low = min(low, low_ch);
          deg++;
        } else if (tin[u] < tin[v]) {
          st.push_back(e_id);
          low = min(low, tin[u]);
        }
      }
      if (p_id == -1) is_cut[v] = (deg > 1);
      return low;
    };
    rep(i, 0, n) if (!tin[i]) dfs(dfs, i, -1);
  }
};
