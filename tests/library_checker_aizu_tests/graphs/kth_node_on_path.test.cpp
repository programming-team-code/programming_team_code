#define PROBLEM "https://judge.yosupo.jp/problem/jump_on_tree"
#include "../template.hpp"

#include "../../../library/graphs/tree_lift/tree_lift.hpp"

#include "../../../library/graphs/lca_rmq/lca_rmq.hpp"

#include "../../../library/graphs/linear_lca/linear_lca.hpp"

#define bit_floor bit_floor_linear
#include "../../../library/graphs/ladder_decomposition/linear_kth_par.hpp"
#undef bit_floor

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
#define kth_path kth_path_tree_lift
#include "../../../library/graphs/tree_lift/kth_path.hpp"
#undef kth_path
#define dist_edges dist_edges_tree_lift
#include "../../../library/graphs/tree_lift/dist_edges.hpp"
#undef dist_edges
	LCA lc(adj);
#include "../../../library/graphs/lca_rmq/next_on_path.hpp"
#define dist_edges dist_edges_lca_rmq
#include "../../../library/graphs/lca_rmq/dist_edges.hpp"
#undef dist_edges
	linear_lca lin_lca(adj);
#define dist_edges dist_edges_linear_lca
#include "../../../library/graphs/linear_lca/dist_edges.hpp"
#undef dist_edges
	linear_kth_par lin_kp(adj);
#define kth_path kth_path_linear
#include "../../../library/graphs/linear_kth_path.hpp"
#undef kth_path
	while (q--) {
		int u, v, k;
		cin >> u >> v >> k;
		int dist_in_edges = dist_edges_tree_lift(u, v);
		assert(dist_in_edges == dist_edges_lca_rmq(u, v));
		assert(dist_in_edges == dist_edges_linear_lca(u, v));
		int res = kth_path_tree_lift(u, v, k);
		assert(res == kth_path_linear(u, v, k));
		cout << res << '\n';
		if (u != v) {
			assert(kth_path_tree_lift(u, v, 0) == u);
			assert(kth_path_linear(u, v, 0) == u);
			assert(kth_path_tree_lift(u, v, 1) == next_on_path(u, v));
			assert(kth_path_linear(u, v, 1) == next_on_path(u, v));
			assert(kth_path_tree_lift(u, v, dist_in_edges - 1) == next_on_path(v, u));
			assert(kth_path_linear(u, v, dist_in_edges - 1) == next_on_path(v, u));
			assert(kth_path_tree_lift(u, v, dist_in_edges) == v);
			assert(kth_path_linear(u, v, dist_in_edges) == v);
			assert(kth_path_tree_lift(u, v, dist_in_edges + 1) == -1);
			assert(kth_path_linear(u, v, dist_in_edges + 1) == -1);
		}
	}
}
