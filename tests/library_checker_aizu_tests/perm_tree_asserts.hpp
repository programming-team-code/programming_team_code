#pragma once
#include "../../library/data_structures/rmq.hpp"
#include "../../library/data_structures/uncommon/permutation_tree.hpp"
void perm_tree_asserts(const vector<int>& a, perm_tree& pt) {
	int n = ssize(a);
	RMQ rmq_min(a, [](int x, int y) {return min(x, y);});
	RMQ rmq_max(a, [](int x, int y) {return max(x, y);});
	auto is_join = pt.is_join;
	auto mn_idx = pt.mn_idx;
	auto mn_val = pt.mn_val;
	auto len = pt.len;
	auto root = pt.root;
	auto adj = pt.adj;
	assert(mn_idx[root] == 0 && mn_val[root] == 0 && len[root] == n);
	if (n == 1) assert(ssize(adj) == 1);
	else assert(n + 1 <= ssize(adj) && ssize(adj) < 2 * n);
	for (int u = 0; u < ssize(adj); u++) {
		{
			int mn_val_rmq = rmq_min.query(mn_idx[u], mn_idx[u] + len[u]);
			assert(mn_val_rmq == mn_val[u]);
			int mx_val_rmq = rmq_max.query(mn_idx[u], mn_idx[u] + len[u]);
			assert(mx_val_rmq - mn_val_rmq + 1 == len[u]);
		}
		if (empty(adj[u])) {
			assert(0 <= u && u < n);
			assert(len[u] == 1);
			assert(u == mn_idx[u]);
			assert(a[u] == mn_val[u]);
			assert(!is_join[u]);
		} else {
			assert(n <= u && u < ssize(adj));
			if (is_join[u]) assert(len[u] >= 2);
			else assert(len[u] >= 3);
			assert(ssize(adj[u]) >= 2);
			assert(mn_idx[u] == mn_idx[adj[u][0]]);
			assert(mn_idx[u] + len[u] == mn_idx[adj[u].back()] + len[adj[u].back()]);
			assert(is_join[u] == (mn_val[u] == mn_val[adj[u][0]] || mn_val[u] == mn_val[adj[u].back()]));
			assert(is_join[u] == (mn_val[u] + len[u] == mn_val[adj[u][0]] + len[adj[u][0]] ||
			                      mn_val[u] + len[u] == mn_val[adj[u].back()] + len[adj[u].back()]));
			for (int i = 1; i < ssize(adj[u]); i++) {
				int prev = adj[u][i - 1], curr = adj[u][i];
				assert(mn_idx[prev] + len[prev] == mn_idx[curr]);
				bool curr_touches = pt.touches(prev, curr);
				assert(is_join[u] == curr_touches);
			}
			if (ssize(adj[u]) <= 10) {
				for (int i = 0; i < ssize(adj[u]); i++) {
					int node_le = adj[u][i];
					int running_min = mn_val[node_le];
					int running_max = mn_val[node_le] + len[node_le];
					int running_sum = len[node_le];
					for (int j = i + 1; j < ssize(adj[u]); j++) {
						int node_ri = adj[u][j];
						running_min = min(running_min, mn_val[node_ri]);
						running_max = max(running_max, mn_val[node_ri] + len[node_ri]);
						running_sum += len[node_ri];
						int mn_val_rmq = rmq_min.query(mn_idx[node_le], mn_idx[node_ri] + len[node_ri]);
						int mx_val_rmq = rmq_max.query(mn_idx[node_le], mn_idx[node_ri] + len[node_ri]);
						int curr_len = mn_idx[node_ri] + len[node_ri] - mn_idx[node_le];
						assert(running_min == mn_val_rmq && running_max == mx_val_rmq + 1 && running_sum == curr_len);
						assert(running_max - running_min >= curr_len);
						assert(curr_len <= len[u]);
						if (curr_len == len[u]) assert(running_max - running_min == curr_len);
						else assert(is_join[u] == (running_max - running_min == curr_len));
					}
				}
			}
			int mn_val_naive = n, mx_val_naive = -1, sum_len_naive = 0;
			for (int v : adj[u]) {
				mn_val_naive = min(mn_val_naive, mn_val[v]);
				mx_val_naive = max(mx_val_naive, mn_val[v] + len[v]);
				sum_len_naive += len[v];
			}
			assert(mn_val_naive == mn_val[u]);
			assert(mx_val_naive == mn_val[u] + len[u]);
			assert(sum_len_naive == len[u]);
		}
	}
}
