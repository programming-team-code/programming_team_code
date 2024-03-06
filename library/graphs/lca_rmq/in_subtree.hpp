/** @file */
#pragma once
#include "lca_rmq.hpp"
/**
 * @code{.cpp}
       LCA lc(adj); //required
 * @endcode
 * @param u,v 2 nodes
 * @returns 1 iff v is in u's subtree
 * @time O(1)
 * @space O(1)
 */
auto in_subtree = [&](int u, int v) -> bool {
	return lc.in[u] <= lc.in[v] && lc.in[v] < lc.in[u] + lc.sub_sz[u];
};
