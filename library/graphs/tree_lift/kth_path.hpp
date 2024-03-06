/** @file */
#pragma once
#include "tree_lift.hpp"
/**
 * @code{.cpp}
       tree_lift tl(adj); //required
 * @endcode
 * @param u,v endpoint nodes of path
 * @param k index into path
 * @returns the node vector<int>({u,p[u],..,lca(u,v),..,p[v],v})[k], or -1, so u if k=0
 * @time O(log(path length(u, v)))
 * @space O(1)
 */
auto kth_path = [&](int u, int v, int k) -> int {
	assert(k >= 0);
	int lca_d = tl.d[tl.lca(u, v)];
	int u_lca = tl.d[u] - lca_d;
	int v_lca = tl.d[v] - lca_d;
	if (k <= u_lca) return tl.kth_par(u, k);
	if (k <= u_lca + v_lca) return tl.kth_par(v, u_lca + v_lca - k);
	return -1;
};
