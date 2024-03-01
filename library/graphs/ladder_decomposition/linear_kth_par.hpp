/** @file */
#pragma once
inline int bit_floor(unsigned x) {return x ? 1 << __lg(x) : 0;}
/**
 * @see Still Simpler Static Level Ancestors by Torben Hagerup, May 2020; https://codeforces.com/blog/entry/126580
 */
template <int x = 3> struct linear_kth_par {
	int n;
	vector<int> d, p, j, dl/*deepest leaf*/, idx;
	vector<vector<int>> l_tbl;
	/**
	 * @code{.cpp}
		   linear_kth_par kp(adj);
		   linear_kth_par<5> kp(adj);
	 * @endcode
	 * @param adj forest (rooted or unrooted)
	 * @time O(n * (2 * x + 1) / (x - 1))
	 * @space O(n * (2 * x + 1) / (x - 1))
	 */
	linear_kth_par(const vector<vector<int>>& adj) : n(ssize(adj)), d(n), p(n, -1), dl(n), idx(n), l_tbl(n) {
		static_assert(x >= 2);
		vector<int> st;
		auto add_j = [&]() -> void {
			j.push_back(st[0]);
			int i = ssize(st) - 1 - (x - 1) * (ssize(j) & -ssize(j));
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
				lad.resize(min((d[leaf] - d[i]) * (2 * x + 1) / (x - 1), d[leaf] + 1), leaf);
				for (int k = 1; k < ssize(lad); k++)
					lad[k] = p[lad[k - 1]];
			}
	}
	/**
	 * @param u query node
	 * @param k number of edges
	 * @returns a node k edges up from u
	 * @time O(x)
	 * @space O(x)
	 */
	inline int kth_par(int u, int k) {
		assert(0 <= k && k <= d[u]);
		if (k < x) {
			while (k--) u = p[u];
			return u;
		}
		int i = bit_floor(unsigned(k / x)), leaf = dl[j[((idx[u] & -i) | i) - 1]];
		return l_tbl[leaf][k + d[leaf] - d[u]];
	}
};
