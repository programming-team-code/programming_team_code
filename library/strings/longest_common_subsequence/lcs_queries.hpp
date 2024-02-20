/** @file */
#pragma once
#include "../../data_structures/bit.hpp"
#include "lcs_dp.hpp"
/**
 * Given strings s, t handle queries for:
 *     given s_ri, t_le, t_ri; calculate size(LCS(s[0, s_ri), t[t_le, t_ri)))
 *
 * @param s,t strings/arrays
 * @param queries queries[i] = {s_ri, t_le, t_ri}
 * @returns res[i] = size(LCS(s.substr(0, queries[i][0]), t.substr(queries[i][1], queries[i][2] - queries[i][1])))
 * @time O(n*m*log(m) + q*log(m) + q*log(q))
 * @space this allocates/returns a O(q) vector, and various vectors are
 * allocated temporarily which are O(n + m + q)
 */
template <class T> vector<int> lcs_queries(const T& s, const T& t, const vector<array<int, 3>>& queries) {
	int n = ssize(s), m = ssize(t), q = ssize(queries);
	vector<vector<array<int, 3>>> qs(n);
	for (int i = 0; i < q; i++) {
		auto [s_ri, t_le, t_ri] = queries[i];
		assert(0 <= s_ri && s_ri <= n);
		assert(0 <= t_le && t_le <= t_ri && t_ri <= m);
		if (s_ri == 0 || t_le == m) continue;
		qs[s_ri - 1].push_back({t_le, t_ri, i});
	}
	lcs_dp lcs(t);
	vector<int> res(q);
	for (int i = 0; i < n; i++) {
		lcs.push_onto_s(s[i]);
		vector<int> init(m), dp_inv(m, -1);
		for (int j = 0; j < m; j++)
			if (lcs.dp[j] == -1) init[j] = 1;
			else dp_inv[lcs.dp[j]] = j;
		BIT<int> bit(init);
		sort(begin(qs[i]), end(qs[i]));
		for (int t_le = 0, j = 0; t_le < m; t_le++) {
			while (j < ssize(qs[i]) && qs[i][j][0] == t_le)
				res[qs[i][j][2]] = bit.sum(t_le, qs[i][j][1]), j++;
			if (dp_inv[t_le] != -1) bit.update(dp_inv[t_le], 1);
		}
	}
	return res;
}
