#pragma once
#include "bridges.hpp"
//! @code
//!   bridges cc(adj, m);
//!   vector<vi> bt = bridge_tree(adj, cc);
//! @endcode
//! @time O(n + m)
//! @space O(n)
vector<vi> bridge_tree(const vector<vector<pii>>& adj,
  const bridges& cc) {
  vector<vi> tree(cc.num_ccs);
  rep(i, 0, sz(adj)) for (auto [u, e_id] : adj[i]) if (
    cc.is_bridge[e_id]) tree[cc.cc_id[i]]
    .push_back(cc.cc_id[u]);
  return tree;
}
