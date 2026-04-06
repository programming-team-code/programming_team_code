#pragma once
#include "bridges.hpp"
//! @code
//!   vector<basic_string<array<int, 2>>> g(n);
//!   auto [num_ccs, br_id, is_br] = bridges(g, m);
//!   auto bt = bridge_tree(g, num_ccs, br_id, is_br);
//! @endcode
//! @time O(n + m)
//! @space O(n)
auto bridge_tree(const auto& g, int num_ccs,
  const vi& br_id, const vi& is_br) {
  vector<vi> tree(num_ccs);
  rep(i, 0, sz(g)) for (auto [u, e_id] : g[i]) if (
    is_br[e_id]) tree[br_id[i]]
    .push_back(br_id[u]);
  return tree;
}
