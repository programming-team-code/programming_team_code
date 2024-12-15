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
//!     adj[u].push_back({v, i});
//!     adj[v].push_back({u, i});
//!   }
//!   auto [num_ccs, br_id, is_br] = bridges(adj, m);
//! @endcode
//! is_br[edge id] = 1 iff bridge edge
//! br_id[v] = id, 0<=id<num_ccs
//! @time O(n + m)
//! @space O(n + m)
template <class G>
tuple<int, vi, vi> bridges(const G& adj, int m) {
  int n = sz(adj), num_ccs = 0, timer = 0;
  vi br_id(n, -1), is_br(m), tin(n), st;
  auto dfs = [&](auto&& self, int v, int p_id) -> int {
    int low = tin[v] = ++timer, siz = sz(st);
    st.push_back(v);
    for (auto [u, e_id] : adj[v])
      if (e_id != p_id && br_id[u] < 0)
        low = min(low, tin[u] ?: self(self, u, e_id));
    if (tin[v] == low) {
      if (p_id != -1) is_br[p_id] = 1;
      rep(i, siz, sz(st)) br_id[st[i]] = num_ccs;
      st.resize(siz);
      num_ccs++;
    }
    return low;
  };
  rep(i, 0, n) if (!tin[i]) dfs(dfs, i, -1);
  return {num_ccs, br_id, is_br};
}
