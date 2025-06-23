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
//! @time O(n + m)
//! @space O(n + m)
/*
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
*/
void cuts_callback(const auto& adj, auto f) {
  int n = ssize(adj), q = 0, s = 0;
  vector<int> tin(n), st(n);
  auto dfs = [&](auto&& self, int v, int p) -> int {
    int low = tin[v] = ++q;
    for (int u : adj[v]) if (u != p) {
      int siz = s, lu = 0;
      low = min(low, tin[u] ?: (lu = self(self, st[s++] = u, v)));
      if (lu >= tin[v]) {
        f(v, vector<int>(begin(st) + siz, begin(st) + s));
        s = siz;
      }
    }
    return low;
  };
  for (int i = 0; i <n; i++) if (!tin[i]) dfs(dfs, i, i);
}
