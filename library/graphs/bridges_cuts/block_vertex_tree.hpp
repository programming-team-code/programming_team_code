#pragma once
#include "cuts.hpp"
//! @code
//!   cuts cc(adj_c, m);
//!   vector<vi> bvt = block_vertex_tree(adj_c, cc);
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
vector<vi> block_vertex_tree(
  const vector<vector<pii>>& adj, const cuts& cc) {
  int n = sz(adj);
  vector<vi> bvt(n + cc.num_bccs);
  vector<bool> vis(cc.num_bccs);
  rep(i, 0, n) {
    for (auto [_, e_id] : adj[i]) {
      int bccid = cc.bcc_id[e_id];
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
