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
  int n = ssize(adj), num_ccs = 0, q = 0, s = 0;
  vector<int> br_id(n, -1), is_br(m), tin(n), st(n);
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
  for (int i = 0; i < n; i++)
    if (!tin[i]) dfs(dfs, i, -1);
  return tuple{num_ccs, br_id, is_br};
}
//! @code
//!   {
//!     vector<vector<pii>> adj(n);
//!     auto [num_ccs, br_id, is_br] = bridges(adj, m);
//!     auto bt = bridge_tree(adj, num_ccs, br_id, is_br);
//!   }
//!   vector<basic_string<array<int, 2>>> adj(n);
//!   auto [num_ccs, br_id, is_br] = bridges(adj, m);
//!   auto bt = bridge_tree(adj, num_ccs, br_id, is_br);
//! @endcode
//! @time O(n + m)
//! @space O(n)
auto bridge_tree(const auto& adj, int num_ccs,
  const vector<int>& br_id, const vector<int>& is_br) {
  vector<basic_string<int>> tree(num_ccs);
  for (int i = 0; i < ssize(adj); i++)
    for (auto [u, e_id] : adj[i])
      if (is_br[e_id]) tree[br_id[i]] += br_id[u];
  return tree;
}
