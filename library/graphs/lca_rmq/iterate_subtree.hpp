/** @file */
#pragma once
#include "lca_rmq.hpp"
/**
 * @see https://codeforces.com/blog/entry/44351
 * @code{.cpp}
       LCA lc(adj); //required
 * @endcode
 * @param u some node
 * @time O(size of u's subtree)
 * @space O(1)
 */
for (int t = lc.in[u]; t < lc.in[u] + lc.sub_sz[u]; t++) {
	int v = lc.order[t];
