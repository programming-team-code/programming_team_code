#define PROBLEM "https://judge.yosupo.jp/problem/jump_on_tree"
#include "../template.hpp"

#include "../../../library/trees/tree_lift/tree_lift.hpp"

#include "../../../library/trees/lca_rmq/lca_rmq.hpp"

#include "../../../library/trees/linear_lca/linear_lca.hpp"

#define bit_floor bit_floor_linear
#include "../../../library/trees/linear_kth_path.hpp"
#undef bit_floor

#include "../compress_tree_asserts.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q;
	cin >> n >> q;
	vector<vector<int>> adj(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	tree_lift tl(adj);
	LCA lc(adj);
	linear_lca lin_lca(adj);
	compress_tree_asserts(adj, lin_lca);
	linear_kth_par lin_kp(adj);
	while (q--) {
		int u, v, k;
		cin >> u >> v >> k;
		int dist_in_edges = tl.dist_edges(u, v);
		assert(dist_in_edges == lc.dist_edges(u, v));
		assert(dist_in_edges == lin_lca.dist_edges(u, v));
		int res = tl.kth_path(u, v, k);
		assert(res == kth_path(lin_lca, lin_kp, u, v, k));
		cout << res << '\n';
		if (u != v) {
			assert(tl.kth_path(u, v, 0) == u);
			assert(kth_path(lin_lca, lin_kp, u, v, 0) == u);
			assert(tl.kth_path(u, v, 1) == lc.next_on_path(u, v));
			assert(kth_path(lin_lca, lin_kp, u, v, 1) == lc.next_on_path(u, v));
			assert(tl.kth_path(u, v, dist_in_edges - 1) == lc.next_on_path(v, u));
			assert(kth_path(lin_lca, lin_kp, u, v, dist_in_edges - 1) == lc.next_on_path(v, u));
			assert(lin_lca.next_on_path(u, v) == lc.next_on_path(u, v));
			assert(lin_lca.next_on_path(v, u) == lc.next_on_path(v, u));
			assert(lin_lca.in_subtree(u, v) == lc.in_subtree(u, v));
			assert(lin_lca.in_subtree(v, u) == lc.in_subtree(v, u));
			assert(tl.kth_path(u, v, dist_in_edges) == v);
			assert(kth_path(lin_lca, lin_kp, u, v, dist_in_edges) == v);
			assert(tl.kth_path(u, v, dist_in_edges + 1) == -1);
			assert(kth_path(lin_lca, lin_kp, u, v, dist_in_edges + 1) == -1);
		}
	}
}
