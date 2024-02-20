/** @file */
#pragma once
#include "tree_lift.hpp"
/**
 * @param tl tree lift
 * @param u,v endpoint nodes of path
 * @returns number of edges on path
 * @time O(log(path length(u, v)))
 * @space O(1)
 */
inline int dist_edges(tree_lift& tl, int u, int v) {
	return tl.d[u] + tl.d[v] - 2 * tl.d[tl.get_lca(u, v)];
}
