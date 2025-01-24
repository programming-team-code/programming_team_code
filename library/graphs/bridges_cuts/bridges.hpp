#pragma once
//! https://cp-algorithms.com/graph/bridge-searching.html
//! @code
//!   {
//!     vector<vector<pii>> adj(n);
//!     auto [num_ccs, br_id, is_br] = bridges(adj, m);
//!   }
//!   vector<basic_string<array<int, 2>>> adj(n);
//!   rep (i, 0, m) {
//!     int u, v;
//!     cin >> u >> v;
//!     u--, v--;
//!     adj[u] += {v, i};
//!     adj[v] += {u, i};
//!   }
//!   auto [num_ccs, br_id, is_br] = bridges(adj, m);
//! @endcode
//! is_br[edge id] = 1 iff bridge edge
//! br_id[v] = id, 0<=id<num_ccs
//! @time O(n + m)
//! @space O(n + m)
auto bridges(const auto& adj, int m) {
  int n = sz(adj), num_ccs = 0, q = 0, s = 0;
  vi br_id(n, -1), is_br(m), tin(n), st(n);
  auto dfs = [&](auto&& self, int v, int p) -> int {
    int low = tin[v] = ++q;
    st[s++] = v;
    for (auto [u, e] : adj[v])
      if (e != p && br_id[u] < 0)
        low = min(low, tin[u] ?: self(self, u, e));
    if (tin[v] == low) {
      if (p != -1) is_br[p] = 1;
      while (br_id[v] < 0) br_id[st[--s]] = num_ccs;
      num_ccs++;
    }
    return low;
  };
  rep(i, 0, n) if (!tin[i]) dfs(dfs, i, -1);
  return tuple{num_ccs, br_id, is_br};
}
