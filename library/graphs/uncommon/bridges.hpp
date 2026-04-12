#pragma once
//! https://cp-algorithms.com/graph/bridge-searching.html
//! @code
//!   vector<basic_string<array<int, 2>>> g(n);
//!   rep (i, 0, m) {
//!     int u, v;
//!     cin >> u >> v;
//!     u--, v--;
//!     g[u] += {v, i};
//!     g[v] += {u, i};
//!   }
//!   auto [num_ccs, br_id, is_br] = bridges(g, m);
//! @endcode
//! is_br[edge id] = 1 iff bridge edge
//! br_id[v] = id, 0<=id<num_ccs
//! @time O(n + m)
//! @space O(n + m)
auto bridges(const auto& g, int m) {
  int n = sz(g), num_ccs = 0, q = 0, s = 0;
  vi br_id(n, -1), is_br(m), tin(n), st(n);
  auto dfs = [&](auto dfs, int u, int p) {
    int low = tin[u] = ++q;
    st[s++] = u;
    for (auto [v, e] : g[u])
      if (e != p && br_id[v] < 0)
        low = min(low, tin[v] ?: dfs(dfs, v, e));
    if (tin[u] == low) {
      if (p != -1) is_br[p] = 1;
      while (br_id[u] < 0) br_id[st[--s]] = num_ccs;
      num_ccs++;
    }
    return low;
  };
  rep(i, 0, n) if (!tin[i]) dfs(dfs, i, -1);
  return tuple{num_ccs, br_id, is_br};
}
