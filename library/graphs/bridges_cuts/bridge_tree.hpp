#pragma once
#include "bridges.hpp"
//! @code
//!   vector<vector<pii>> adj(n);
//!   bridges br(adj, m);
//!   vector<vi> bt = bridge_tree(adj, br);
//!   vector<basic_string<array<int, 2>>> adj1(n);
//!   bridges br1(adj1, m);
//!   vector<vi> bt1 = bridge_tree(adj1, br1);
//! @endcode
//! @time O(n + m)
//! @space O(n)
template<class G>
vector<vi> bridge_tree(const G& adj, int num_ccs,
  const vi& br_id, const vi& is_br) {
  vector<vi> tree(num_ccs);
  rep(i, 0, sz(adj)) for (auto [u, e_id] : adj[i]) if (
    is_br[e_id]) tree[br_id[i]]
    .push_back(br_id[u]);
  return tree;
}
