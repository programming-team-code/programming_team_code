#pragma once
#include "bridges.hpp"
//! @code
//!   bridges br(adj_br, m);
//!   vector<vi> bt = bridge_tree(adj_br, br);
//! @endcode
//! @time O(n + m)
//! @space O(n)
vector<vi> bridge_tree(const vector<vector<pii>>& adj,
  const bridges& br) {
  vector<vi> tree(br.num_ccs);
  rep(i, 0, sz(adj)) for (auto [u, e_id] : adj[i]) if (
    br.is_bridge[e_id]) tree[br.cc_id[i]]
    .push_back(br.cc_id[u]);
  return tree;
}
