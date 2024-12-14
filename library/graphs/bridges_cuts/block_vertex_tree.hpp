#pragma once
#include "cuts.hpp"
//! @code
//!   vector<vector<pii>> adj(n);
//!   cuts cc(adj, m);
//!   vector<vi> bvt = block_vertex_tree(adj, cc);
//!   vector<basic_string<array<int, 2>>> adj1(n);
//!   cuts cc1(adj1, m);
//!   vector<vi> bvt1 = block_vertex_tree(adj1, cc1);
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
template<class G>
vector<vi> block_vertex_tree(const G& adj,
  const cuts<G>& cc) {
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
