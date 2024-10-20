//! https://cp-algorithms.com/graph/cutpoints.html
//! @code
//!   vector<vector<pii>> adj_c(n);
//!   rep (i, 0, m) {
//!     int u, v;
//!     cin >> u >> v;
//!     u--, v--;
//!     //self edges not allowed
//!     adj_c[u].emplace_back(v, i);
//!     adj_c[v].emplace_back(u, i);
//!   }
//!   auto [num_bccs, is_cut, bcc_id] = cuts(adj_c, m);
//! @endcode
//! is_cut[v] = 1 iff cut node
//! bcc_id[edge id] = id, 0<=id<num_bccs
//! @time O(n + m)
//! @space O(n + m)
struct cuts {
  int num_bccs = 0;
  vector<bool> is_cut;
  vector<int> bcc_id;
  cuts(const vector<vector<pair<int, int>>>& adj, int m):
    is_cut(ssize(adj)), bcc_id(m, -1) {
    int n = ssize(adj), timer = 1;
    vector<int> tin(n), st;
    auto dfs = [&](auto&& self, int v, int p_id) -> int {
      int low = tin[v] = timer++, deg = 0;
      for (auto [u, e_id] : adj[v]) {
        assert(v != u);
        if (e_id == p_id) continue;
        if (!tin[u]) {
          int siz = ssize(st);
          st.push_back(e_id);
          int low_ch = self(self, u, e_id);
          if (low_ch >= tin[v]) {
            is_cut[v] = 1;
            for (int i = siz; i < ssize(st); i++)
              bcc_id[st[i]] = num_bccs;
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
    for (int i = 0; i < n; i++)
      if (!tin[i]) dfs(dfs, i, -1);
  }
};
