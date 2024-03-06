/** @file */
#pragma once
#include "lca_rmq.hpp"
/**
 * @code{.cpp}
       LCA lca(adj); //required
 * @endcode
 * @param u,v endpoint nodes of path
 * @returns number of edges on path
 * @time O(1)
 * @space O(1)
 */
auto dist_edges = [&](int u, int v) -> int {
	return lca.d[u] + lca.d[v] - 2 * lca.d[lca.get_lca(u, v)];
};
