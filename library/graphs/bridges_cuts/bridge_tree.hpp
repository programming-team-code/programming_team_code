#pragma once
#include "bridges.hpp"
//! @code
//!   vector<vector<pii>> adj(n);
//!   bridges br(adj, m);
//!   vector<vi> bt = bridge_tree(adj, br);
//! @endcode
//! @time O(n + m)
//! @space O(n)
vector<vi> bridge_tree(const vector<vector<pii>>& adj,
  const bridges& br) {
  vector<vi> tree(br.num_ccs);
  rep(i, 0, sz(adj)) for (auto [u, e_id] : adj[i]) if (
    br.is_bridge[e_id]) tree[br.br_id[i]]
    .push_back(br.br_id[u]);
  return tree;
}
