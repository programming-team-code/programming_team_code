/** @file */
#pragma once
/**
 * DSU with support for parity of path to root for online bipartite check
 *
 * @see https://cp-algorithms.com /data_structures/disjoint_set_union.html
 * support-the-parity-of-the-path-length-checking-bipartiteness-online
 */
struct dsu_bipartite {
	int num_sets;
	vector<int> p, is_bi, parity;
	dsu_bipartite(int n) : num_sets(n), p(n, -1), is_bi(n, 1), parity(n) {}
	int find(int u) {
		if (p[u] < 0) return u;
		int root = find(p[u]);
		parity[u] ^= parity[p[u]];
		return p[u] = root;
	}
	bool join(int u, int v) {
		int root_u = find(u), root_v = find(v);
		if (root_u == root_v) {
			if (parity[u] == parity[v]) is_bi[root_u] = 0;
			return 0;
		}
		if (p[root_u] > p[root_v]) {
			swap(u, v);
			swap(root_u, root_v);
		}
		is_bi[root_u] &= is_bi[root_v];
		parity[root_v] = parity[v] ^ 1 ^ parity[u];
		p[root_u] += p[root_v], p[root_v] = root_u, num_sets--;
		return 1;
	}
	inline int size(int u) { return -p[find(u)]; }
	inline bool same_set(int u, int v) { return find(u) == find(v); }
	inline bool is_bipartite(int u) { return is_bi[find(u)]; }
};
