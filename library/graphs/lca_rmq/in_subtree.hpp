/** @file */
#pragma once
#include "lca_rmq.hpp"
/**
 * @code{.cpp}
       LCA lca(adj); //required
 * @endcode
 * @param u,v 2 nodes
 * @returns 1 iff v is in u's subtree
 * @time O(1)
 * @space O(1)
 */
auto in_subtree = [&](int u, int v) -> bool {
	return lca.in[u] <= lca.in[v] && lca.in[v] < lca.in[u] + lca.sub_sz[u];
};
