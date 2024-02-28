/** @file */
#pragma once
inline int bit_floor(unsigned x) {return x ? 1 << __lg(x) : 0;}
/**
 * @see Still Simpler Static Level Ancestors by Torben Hagerup, May 2020
 */
struct linear_kth_par {
	int n;
	vector<int> d, p, j, dl/*deepest leaf*/, idx;
	vector<vector<int>> l_tbl;
	/**
	 * @param adj forest (rooted or unrooted)
	 * @time O(n)
	 * @space O(n)
	 */
	linear_kth_par(const vector<vector<int>>& adj) : n(ssize(adj)), d(n), p(n, -1), dl(n), idx(n), l_tbl(n) {
		vector<int> st;
		auto add_j = [&]() -> void {
			j.push_back(st[0]);
			int i = ssize(st) - 1 - 2 * (ssize(j) & -ssize(j));
			if (i > 0) j.back() = st[i];
		};
		auto dfs = [&](auto&& self, int u) -> void {
			st.push_back(u);
			add_j();
			idx[u] = ssize(j);
			dl[u] = u;
			for (int v : adj[u])
				if (v != p[u]) {
					d[v] = d[p[v] = u] + 1;
					self(self, v);
					add_j();
					if (d[dl[v]] > d[dl[u]]) dl[u] = dl[v];
				}
			st.pop_back();
		};
		for (int i = 0; i < n; i++)
			if (p[i] == -1) p[i] = i, dfs(dfs, i);
		for (int i = 0; i < n; i++)
			if (p[i] == i || dl[p[i]] != dl[i]) {
				int leaf = dl[i];
				auto& lad = l_tbl[leaf];
				lad.resize(min((d[leaf] - d[i]) * 7 / 2, d[leaf] + 1), leaf);
				for (int k = 1; k < ssize(lad); k++)
					lad[k] = p[lad[k - 1]];
			}
	}
	/**
	 * @param u query node
	 * @param k number of edges
	 * @returns a node k edges up from u
	 * @time O(1)
	 * @space O(1)
	 */
	inline int kth_par(int u, int k) {
		assert(0 <= k && k <= d[u]);
		if (k == 0) return u;
		if (k == 1) return p[u];
		if (k == 2) return p[p[u]];
		int i = bit_floor(unsigned(k / 3)), leaf = dl[j[((idx[u] & -i) | i) - 1]];
		return l_tbl[leaf][k + d[leaf] - d[u]];
	}
};
