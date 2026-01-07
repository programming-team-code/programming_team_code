//! https://cp-algorithms.com/graph/cutpoints.html
//! @code
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
  int n = ssize(adj), num_bccs = 0, q = 0, s = 0;
  vector<int> bcc_id(m, -1), is_cut(n), tin(n), st(m);
  auto dfs = [&](auto&& self, int u, int p) -> int {
    int low = tin[u] = ++q;
    for (auto [v, e] : adj[u]) {
      assert(u != v);
      if (e == p) continue;
      if (tin[v] < tin[u]) st[s++] = e;
      int lu = -1;
      low = min(low, tin[v] ?: (lu = self(self, v, e)));
      if (lu >= tin[u]) {
        is_cut[u] = p >= 0 || tin[u] + 1 < tin[v];
        while (bcc_id[e] < 0) bcc_id[st[--s]] = num_bccs;
        num_bccs++;
      }
    }
    return low;
  };
  for (int i = 0; i < n; i++)
    if (!tin[i]) dfs(dfs, i, -1);
  return tuple{num_bccs, bcc_id, is_cut};
}
//! @code
//!   vector<basic_string<array<int, 2>>> adj(n);
//!   auto [num_bccs, bcc_id, is_cut] = cuts(adj, m);
//!   auto bvt = block_vertex_tree(adj, num_bccs, bcc_id);
//!
//!   //to loop over each unique bcc containing a node u:
//!   for (int bccid : bvt[v]) {
//!     bccid -= n;
//!   }
//!   //to loop over each unique node inside a bcc:
//!   for (int v : bvt[bccid + n]) {}
//! @endcode
//! [0, n) are original nodes
//! [n, n + num_bccs) are BCC nodes
//! @time O(n + m)
//! @time O(n)
auto block_vertex_tree(const auto& adj, int num_bccs,
  const vector<int>& bcc_id) {
  int n = ssize(adj);
  vector<vector<int>> bvt(n + num_bccs);
  vector<bool> vis(num_bccs);
  for (int i = 0; i < n; i++) {
    for (auto [_, e_id] : adj[i]) {
      int bccid = bcc_id[e_id];
      if (!vis[bccid]) {
        vis[bccid] = 1;
        bvt[i].push_back(bccid + n);
        bvt[bccid + n].push_back(i);
      }
    }
    for (int bccid : bvt[i]) vis[bccid - n] = 0;
  }
  return bvt;
}
