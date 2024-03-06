#define PROBLEM "https://judge.yosupo.jp/problem/jump_on_tree"
#include "../template.hpp"

#include "../../../library/graphs/tree_lift/tree_lift.hpp"
#include "../../../library/graphs/tree_lift/kth_path.hpp"

#include "../../../library/graphs/lca_rmq/lca_rmq.hpp"

#include "../../../library/graphs/linear_lca/linear_lca.hpp"

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
#define dist_edges dist_edges_tree_lift
#include "../../../library/graphs/tree_lift/dist_edges.hpp"
#undef dist_edges
	LCA lca(adj);
#include "../../../library/graphs/lca_rmq/next_on_path.hpp"
#define dist_edges dist_edges_lca_rmq
#include "../../../library/graphs/lca_rmq/dist_edges.hpp"
#undef dist_edges
	linear_lca lin_lca(adj);
#define dist_edges dist_edges_linear_lca
#include "../../../library/graphs/linear_lca/dist_edges.hpp"
#undef dist_edges
	while (q--) {
		int u, v, k;
		cin >> u >> v >> k;
		int dist_in_edges = dist_edges_tree_lift(u, v);
		if (k > dist_in_edges)
			cout << -1 << '\n';
		else
			cout << kth_path(tl, u, v, k) << '\n';
		assert(dist_in_edges == dist_edges_lca_rmq(u, v));
		assert(dist_in_edges == dist_edges_linear_lca(u, v));
		if (u != v) {
			assert(kth_path(tl, u, v, 0) == u);
			assert(kth_path(tl, u, v, 1) == next_on_path(u, v));
			assert(kth_path(tl, u, v, dist_in_edges - 1) == next_on_path(v, u));
			assert(kth_path(tl, u, v, dist_in_edges) == v);
		}
	}
}
