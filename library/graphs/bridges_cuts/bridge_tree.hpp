//! @file
#pragma once
#include "bridges.hpp"
//! Never adds multiple edges as bridges.hpp
//! correctly marks them as non-bridges.
//! @code{.cpp}
//!     bridges cc(adj, m);
//!     vector<vi> bt = bridge_tree(adj, cc);
//! @endcode
//! @param adj undirected graph
//! @param cc what's calculated by bridges
//! @returns adjacency list of bridge tree
//! @time O(n + m)
//! @space besides the O(n + m) sized params, this
//! function allocates and returns `tree` vector,
//! which is O(n)
vector<vi> bridge_tree(
  const vector<vector<pii>>& adj,
  const bridges& cc) {
  vector<vi> tree(cc.num_2_edge_ccs);
  rep(i, 0, sz(adj)) for (auto [u, e_id] :
    adj[i]) if (cc.is_bridge[e_id])
    tree[cc.two_edge_ccid[i]]
      .push_back(cc.two_edge_ccid[u]);
  return tree;
}
