/** @file */
#pragma once
#include "lca_rmq.hpp"
/**
 * @code{.cpp}
       LCA lc(adj); //required
 * @endcode
 * @param u,v endpoint nodes of path
 * @returns number of edges on path
 * @time O(1)
 * @space O(1)
 */
auto dist_edges = [&](int u, int v) -> int {
	return lc.d[u] + lc.d[v] - 2 * lc.d[lc.get_lca(u, v)];
};
