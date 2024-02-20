/** @file */
#pragma once
#include "linear_lca.hpp"
/**
 * @param lca linear lca
 * @param u,v endpoint nodes of path
 * @returns number of edges on path
 * @time O(1)
 * @space O(1)
 */
inline int dist_edges(linear_lca& lca, int u, int v) {
	return lca.d[u] + lca.d[v] - 2 * lca.d[lca.get_lca(u, v)];
}
