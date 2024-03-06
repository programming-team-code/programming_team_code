#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"
#include "../../../library/trees/centroid_decomp/count_paths_per_node.hpp"
#include "../../../library/data_structures/uncommon/dsu_restorable.hpp"

#include "../../../library/trees/tree_lift/tree_lift.hpp"

#include "../../../library/trees/centroid_decomp/count_paths_per_length.hpp"

vector<vector<int64_t>> naive(const vector<vector<int>>& adj, dsu_restorable& dsu) {
	tree_lift tl(adj);
	int n = ssize(adj);
	vector<vector<int64_t>> cnts_naive(n + 1, vector<int64_t>(n, 0));
	for (int u = 0; u < n; u++) {
		for (int v = u; v < n; v++) {
			if (dsu.same_set(u, v)) {
				int path_length_edges = tl.dist_edges(u, v);
				for (int i = 0; i <= path_length_edges; i++)
					cnts_naive[path_length_edges][tl.kth_path(u, v, i)]++;
			}
		}
	}
	return cnts_naive;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	for (int n = 1; n <= 100; n++) {
		vector<vector<int>> adj(n);
		dsu_restorable dsu(n);
		for (int i = 0; i < n - 2; i++) {
			int u = get_rand<int>(0, n - 1);
			int v = get_rand<int>(0, n - 1);
			if (u == v)
				continue;
			if (dsu.join(u, v)) {
				adj[u].push_back(v);
				adj[v].push_back(u);
			}
		}
		vector<vector<int64_t>> cnts_naive = naive(adj, dsu);
		for (int k = 1; k <= n; k++)
			assert(count_paths_per_node(adj, k) == cnts_naive[k]);
		vector<int64_t> num_paths_len = count_paths_per_length(adj);
		for (int k = 1; k < n; k++) {
			vector<int64_t> count_paths = count_paths_per_node(adj, k);
			int64_t total_paths = accumulate(begin(count_paths), end(count_paths), 0LL);
			assert(total_paths % (k + 1) == 0);
			total_paths /= k + 1;
			assert(num_paths_len[k] == total_paths);
		}
	}
	cout << "Hello World\n";
	return 0;
}
