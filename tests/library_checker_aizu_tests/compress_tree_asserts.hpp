#pragma once
#define RMQ KACTL_RMQ
#define LCA KACTL_LCA
#include "../../kactl/content/graph/CompressTree.h"
#undef RMQ
#undef LCA
#include "../../library/contest/random.hpp"
void compress_tree_asserts(vector<vector<int>> adj, linear_lca& lin_lca) {
	int n = ssize(adj);
	vector<bool> used(n);
	KACTL_LCA kactl_lca(adj);
	{
		auto [parent, to_node] = lin_lca.compress_tree({});
		assert(empty(parent) && empty(to_node));
	}
	for (int tests = 0; tests < 10; tests++) {
		vector<int> subset;
		{
			int subset_size = get_rand(1, min(n, 10));
			while (subset_size--) {
				int u = get_rand(0, n - 1);
				if (!used[u]) {
					used[u] = 1;
					subset.push_back(u);
				}
			}
		}
		auto kactl_res = compressTree(kactl_lca, subset);
		auto [parent, to_node] = lin_lca.compress_tree(subset);
		assert(ssize(parent) == ssize(to_node) && ssize(parent) == ssize(kactl_res));
		for (int i = 0; i < ssize(parent); i++) {
			assert(to_node[i] == kactl_res[i].second);
			assert(parent[i] < i);
			if (i > 0) assert(parent[i] == kactl_res[i].first);
			else assert(parent[i] == -1);
		}
		for (int u : subset) used[u] = 0;
	}
}
