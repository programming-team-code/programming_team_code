/** @file */
#pragma once
#include "tree_lift.hpp"
/**
 * @code{.cpp}
       tree_lift tl(adj); //required
 * @endcode
 * @param u,v endpoint nodes of path
 * @returns number of edges on path
 * @time O(log(path length(u, v)))
 * @space O(1)
 */
auto dist_edges = [&](int u, int v) -> int {
	return tl.d[u] + tl.d[v] - 2 * tl.d[tl.lca(u, v)];
};
