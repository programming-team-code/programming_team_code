/** @file */
#pragma once
#include "in_subtree.hpp"
/**
 * @see https://github.com/kth-competitive-programming /kactl/blob/main/content/graph/CompressTree.h
 *
 * Given a rooted tree and a subset S of nodes, compute the minimal subtree
 * that contains all the nodes by adding all (at most |S|-1) pairwise LCA's and
 * compressing edges.
 *
 * @code{.cpp}
       auto [par, orig_node] = lin_lca.compress_tree(subset);
 * @endcode
 *
 * @param subset subset of nodes
 * @returns vectors `par`, `orig_node`, for node i in compressed tree:
 *          par[i] = parent of i in compressed tree; par[0] == -1; par[i] < i
 *          orig_node[i] = corresponding node in big tree
 * @time O(k log k); k = ssize(subset)
 * @space O(k) vectors are allocated and returned
 */
array<vector<int>, 2> compress_tree(vector<int> subset) {
	auto cmp = [&](int u, int v) {return in[u] < in[v];};
	sort(begin(subset), end(subset), cmp);
	for (int i = 1, siz = ssize(subset); i < siz; i++)
		subset.push_back(lca(subset[i - 1], subset[i]));
	sort(begin(subset), end(subset), cmp);
	subset.erase(unique(begin(subset), end(subset)), end(subset));
	return {mono_st(subset, [&](int u, int v) {return in_subtree(u, v);}), subset};
}
