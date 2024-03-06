/** @file */
#pragma once
#include "linear_lca.hpp"
/**
 * @code{.cpp}
       linear_lca lin_lca(adj); //required
 * @endcode
 * @param u,v endpoint nodes of path
 * @returns number of edges on path
 * @time O(1)
 * @space O(1)
 */
auto dist_edges = [&](int u, int v) -> int {
	return lin_lca.d[u] + lin_lca.d[v] - 2 * lin_lca.d[lin_lca.lca(u, v)];
};
