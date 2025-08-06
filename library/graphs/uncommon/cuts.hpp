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
//!   auto [num_bccs, bcc_id, is_cut] = cuts(adj, m);
//! @endcode
//! is_cut[v] = 1 iff cut node
//! bcc_id[edge id] = id, 0<=id<num_bccs
//! @time O(n + m)
//! @space O(n + m)
auto cuts(const auto& adj, int m) {
  int n = sz(adj), num_bccs = 0, q = 0, s = 0;
  vi bcc_id(m, -1), is_cut(n), tin(n), st(m);
  auto dfs = [&](auto&& self, int v, int p) -> int {
    int low = tin[v] = ++q;
    for (auto [u, e] : adj[v]) {
      assert(v != u);
      if (e == p) continue;
      if (tin[u] < tin[v]) st[s++] = e;
      int lu = -1;
      low = min(low, tin[u] ?: (lu = self(self, u, e)));
      if (lu >= tin[v]) {
        is_cut[v] = p >= 0 || tin[v] + 1 < tin[u];
        while (bcc_id[e] < 0) bcc_id[st[--s]] = num_bccs;
        num_bccs++;
      }
    }
    return low;
  };
  rep(i, 0, n) if (!tin[i]) dfs(dfs, i, -1);
  return tuple{num_bccs, bcc_id, is_cut};
}
