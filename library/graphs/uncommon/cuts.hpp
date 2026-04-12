#pragma once
//! https://cp-algorithms.com/graph/cutpoints.html
//! @code
//!   vector<basic_string<array<int, 2>>> g(n);
//!   rep (i, 0, m) {
//!     int u, v;
//!     cin >> u >> v;
//!     u--, v--;
//!     //self edges not allowed
//!     g[u] += {v, i};
//!     g[v] += {u, i};
//!   }
//!   auto [num_bccs, bcc_id, is_cut] = cuts(g, m);
//! @endcode
//! is_cut[v] = 1 iff cut node
//! bcc_id[edge id] = id, 0<=id<num_bccs
//! @time O(n + m)
//! @space O(n + m)
auto cuts(const auto& g, int m) {
  int n = sz(g), num_bccs = 0, q = 0, s = 0;
  vi bcc_id(m, -1), is_cut(n), tin(n), st(m);
  auto dfs = [&](auto dfs, int u, int p) {
    int low = tin[u] = ++q;
    for (auto [v, e] : g[u]) {
      assert(u != v);
      if (e == p) continue;
      if (tin[v] < tin[u]) st[s++] = e;
      int lu = -1;
      low = min(low, tin[v] ?: (lu = dfs(dfs, v, e)));
      if (lu >= tin[u]) {
        is_cut[u] = p >= 0 || tin[u] + 1 < tin[v];
        while (bcc_id[e] < 0) bcc_id[st[--s]] = num_bccs;
        num_bccs++;
      }
    }
    return low;
  };
  rep(i, 0, n) if (!tin[i]) dfs(dfs, i, -1);
  return tuple{num_bccs, bcc_id, is_cut};
}
