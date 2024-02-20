/** @file */
#pragma once
#include "lca_rmq.hpp"
/**
 * @see https://codeforces.com/blog/entry/44351
 * @code{.cpp}
       LCA lca(adj);
       iterate_subtree(lca, u, [&](int v) {
           //v is in u's subtree
       });
 * @endcode
 * @param lca lca via rmq
 * @param u some node
 * @param f lambda which runs on each node in u's subtree (including u)
 * @time O(size of u's subtree)
 * @space O(1)
 */
template <class F> void iterate_subtree(LCA& lca, int u, F f) {
	for (int i = lca.in[u]; i < lca.in[u] + lca.sub_sz[u]; i++)
		f(lca.order[i]);
}
