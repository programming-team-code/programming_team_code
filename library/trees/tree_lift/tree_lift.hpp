/** @file */
#pragma once
/**
 * @see https://github.com/ucf-programming-team/hackpack-cpp /blob/master/content/graphs/TreeLifting.h
 * Calculate jumps up a tree, to support fast upward jumps and LCAs.
 */
struct tree_lift {
	int n;
	vector<int> d, p, j;
	/**
	 * @param adj forest (rooted or unrooted)
	 * @time O(n)
	 * @space O(n) for d, p, j vectors
	 */
	tree_lift(const vector<vector<int>>& adj): n(ssize(adj)), d(n), p(n, -1), j(n, -1) {
		auto dfs = [&](auto&& self, int u) -> void {
			int jump = (d[u] + d[j[j[u]]] == 2 * d[j[u]]) ? j[j[u]] : u;
			for (int v : adj[u])
				if (v != p[u])
					d[v] = d[p[v] = u] + 1, j[v] = jump, self(self, v);
		};
		for (int i = 0; i < n; i++)
			if (j[i] == -1) j[i] = i, dfs(dfs, i);
	}
	/**
	 * @param u query node
	 * @param k number of edges
	 * @returns a node k edges up from u. With k=1, this returns u's parent.
	 * @time O(log k)
	 * @space O(1)
	 */
	inline int kth_par(int u, int k) {
		assert(0 <= k && k <= d[u]);
		int anc_d = d[u] - k;
		while (d[u] > anc_d) u = d[j[u]] >= anc_d ? j[u] : p[u];
		return u;
	}
	/**
	 * @param u,v 2 nodes in the same component
	 * @returns lca of u, v
	 * @time O(log(path length(u, v)))
	 * @space O(1)
	 */
	inline int lca(int u, int v) {
		if (d[u] < d[v]) swap(u, v);
		u = kth_par(u, d[u] - d[v]);
		while (u != v)
			if (j[u] != j[v]) u = j[u], v = j[v];
			else u = p[u], v = p[v];
		return u;
	}
#include "../dist_edges.hpp"
#include "kth_path.hpp"
};
