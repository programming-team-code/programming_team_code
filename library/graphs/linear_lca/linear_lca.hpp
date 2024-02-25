/** @file */
#pragma once
inline int bit_floor(unsigned x) {return x ? 1 << __lg(x) : 0;}
/**
 * @see On Finding Lowest Common Ancestors: Simplification and Parallelization
 * by Baruch Schieber, Uzi Vishkin, April 1987
 */
struct linear_lca {
	vector<vector<int>> adj;
	int n;
	vector<int> d, head, order;
	vector<unsigned> in_label, ascendant;
	/**
	 * @param a_adj forest (rooted or unrooted)
	 * @time O(n)
	 * @space O(n)
	 */
	linear_lca(const vector<vector<int>>& a_adj) : adj(a_adj), n(size(adj)), d(n), head(n + 1), in_label(n), ascendant(n) {
		for (int i = 0; i < n; i++)
			if (in_label[i] == 0) dfs(i, i);
		for (int u : order) {
			int x = in_label[u];
			ascendant[u] = (x & -x) | ascendant[head[x]];
		}
	}
	void dfs(int u, int p) {
		order.push_back(u);
		in_label[u] = ssize(order);
		for (int v : adj[u])
			if (v != p) {
				d[v] = 1 + d[u];
				dfs(v, u);
				if (__builtin_ctz(in_label[v]) > __builtin_ctz(in_label[u]))
					in_label[u] = in_label[v];
			}
		head[in_label[u]] = p;
	}
	inline int lift(int u, unsigned j) {
		auto k = bit_floor(ascendant[u] ^ j);
		return k == 0 ? u : head[(in_label[u] & -k) | k];
	}
	/**
	 * @param u,v nodes
	 * @returns lca of u, v
	 * @time O(1)
	 * @space O(1)
	 */
	inline int get_lca(int u, int v) {
		auto [x, y] = minmax(in_label[u], in_label[v]);
		auto j = ascendant[u] & ascendant[v] & -bit_floor((x - 1) ^ y);
		return d[u = lift(u, j)] < d[v = lift(v, j)] ? u : v;
	}
};
