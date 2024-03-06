/** @file */
#pragma once
#include "lca_rmq.hpp"
/**
 * @see https://codeforces.com/blog/entry/44351
 * @code{.cpp}
       LCA lca(adj); //required
 * @endcode
 * @param u some node
 * @time O(size of u's subtree)
 * @space O(1)
 */
for (int t = lca.in[u]; t < lca.in[u] + lca.sub_sz[u]; t++) {
	int v = lca.order[t];
