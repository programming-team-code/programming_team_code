/** @file */
#pragma once
#include "linear_lca/linear_lca.hpp"
#include "ladder_decomposition/linear_kth_par.hpp"
/**
 * @code{.cpp}
       linear_lca lin_lca(adj); //required
       linear_kth_par lin_kp(adj); //required
 * @endcode
 * @param u,v endpoint nodes of path
 * @param k index into path
 * @returns the node vector<int>({u,p[u],..,lca(u,v),..,p[v],v})[k], so u if k=0
 * @time O(1)
 * @space O(1)
 */
auto kth_path = [&](int u, int v, int k) -> int {
	int lca_d = tl.d[tl.get_lca(u, v)];
	int u_lca = tl.d[u] - lca_d;
	int v_lca = tl.d[v] - lca_d;
	return k <= u_lca ? tl.kth_par(u, k) : tl.kth_par(v, u_lca + v_lca - k);
};
