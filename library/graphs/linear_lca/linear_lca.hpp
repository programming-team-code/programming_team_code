/** @file */
#pragma once
inline int bit_floor(unsigned x) {return x ? 1 << __lg(x) : 0;}
/**
 * @see On Finding Lowest Common Ancestors: Simplification and Parallelization
 * by Baruch Schieber, Uzi Vishkin, April 1987
 */
struct linear_lca {
	vector<vector<int>> adj;
	int n, timer = 1;
	vector<int> d, par_head;
	vector<unsigned> in_label, ascendant;
	/**
	 * @param a_adj forest (rooted or unrooted)
	 * @time O(n)
	 * @space O(n)
	 */
	linear_lca(const vector<vector<int>>& a_adj) : adj(a_adj), n(size(adj)), d(n), par_head(n + 1), in_label(n), ascendant(n) {
		for (int i = 0; i < n; i++)
			if (in_label[i] == 0) {
				dfs1(i, -1);
				ascendant[i] = in_label[i];
				dfs2(i, -1);
			}
	}
	void dfs1(int u, int p) {
		in_label[u] = timer++;
		for (int v : adj[u])
			if (v != p) {
				d[v] = 1 + d[u];
				dfs1(v, u);
				if (__builtin_ctz(in_label[v]) > __builtin_ctz(in_label[u]))
					in_label[u] = in_label[v];
			}
	}
	void dfs2(int u, int p) {
		for (int v : adj[u])
			if (v != p) {
				ascendant[v] = ascendant[u];
				if (in_label[v] != in_label[u]) {
					par_head[in_label[v]] = u;
					ascendant[v] += in_label[v] & -in_label[v];
				}
				dfs2(v, u);
			}
	}
	inline int lift(int u, unsigned j) {
		auto k = bit_floor(ascendant[u] ^ j);
		return k == 0 ? u : par_head[(in_label[u] & -k) | k];
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
