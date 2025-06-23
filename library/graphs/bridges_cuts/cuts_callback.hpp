#pragma once
//! https://cp-algorithms.com/graph/cutpoints.html
//! @code
//!   {
//!     vector<vector<pii>> adj(n);
//!     auto [num_bccs, bcc_id, is_cut] = cuts(adj, m);
//!   }
//!   vector<basic_string<array<int, 2>>> adj(n);
//!   rep (i, 0, m) {
//!     int u, v;
//!     cin >> u >> v;
//!     u--, v--;
//!     //self edges not allowed
//!     adj[u] += {v, i};
//!     adj[v] += {u, i};
//!   }
//!   cuts_callback(adj, [&](int v, const vi& nodes_bcc) {
//!   });
//! @endcode
//! @time O(n + m)
//! @space O(n + m)
void cuts_callback(const auto& adj, auto f) {
  int n = sz(adj), q = 0, s = 0;
  vi tin(n), st(n);
  auto dfs = [&](auto&& self, int v, int p) -> int {
    int low = tin[v] = ++q;
    for (int u : adj[v])
      if (u != p) {
        int siz = s, lu = 0;
        low = min(low,
          tin[u] ?: (lu = self(self, st[s++] = u, v)));
        if (lu >= tin[v]) {
          st[s++] = v;
          f(vi(siz + all(st) - (n - s)));
          s = siz;
        }
      }
    return low;
  };
  rep(i, 0, n) if (!tin[i]) dfs(dfs, i, i);
}
