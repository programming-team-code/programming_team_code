#pragma once
#include "cuts.hpp"
//! @code
//!   {
//!     vector<vector<pii>> adj(n);
//!     auto [num_bccs, bcc_id, is_cut] = cuts(adj, m);
//!     auto bvt = block_vertex_tree(adj,
//!       num_bccs, bcc_id);
//!   }
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
  const vi& bcc_id) {
  int n = sz(adj);
  vector<vi> bvt(n + num_bccs);
  vector<bool> vis(num_bccs);
  rep(i, 0, n) {
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
