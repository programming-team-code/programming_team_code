/** @file */
#pragma once
#include "linear_lca.hpp"
#include "ladder_decomposition/linear_kth_par.hpp"
/**
 * @param lin_lca,lin_kp linear lca and kth parent
 * @param u,v endpoint nodes of path
 * @param k index into path
 * @returns the node vector<int>({u,p[u],..,lca(u,v),..,p[v],v})[k], or -1, so u if k=0
 * @time O(1)
 * @space O(1)
 */
template <int X> int kth_path(linear_lca& lin_lca, linear_kth_par<X>& lin_kp, int u, int v, int k) {
	assert(k >= 0);
	int lca_d = lin_kp.d[lin_lca.lca(u, v)];
	int u_lca = lin_kp.d[u] - lca_d;
	int v_lca = lin_kp.d[v] - lca_d;
	if (k <= u_lca) return lin_kp.kth_par(u, k);
	if (k <= u_lca + v_lca) return lin_kp.kth_par(v, u_lca + v_lca - k);
	return -1;
};
