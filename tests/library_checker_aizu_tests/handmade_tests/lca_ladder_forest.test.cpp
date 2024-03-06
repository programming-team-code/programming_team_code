#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"
#include "../../../library/data_structures/uncommon/dsu_restorable.hpp"

#include "../../../library/graphs/tree_lift/tree_lift.hpp"

#include "../../../library/graphs/lca_rmq/lca_rmq.hpp"

#include "../../../library/graphs/linear_lca/linear_lca.hpp"

#include "../../../library/graphs/ladder_decomposition/ladder_decomposition.hpp"

#define bit_floor bit_floor_2
#include "../../../library/graphs/ladder_decomposition/linear_kth_par.hpp"
#undef bit_floor

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
		ladder lad(adj);
		linear_kth_par<2> linear_kp_2(adj);
		linear_kth_par lin_kp(adj);
		linear_kth_par<4> linear_kp_4(adj);
		linear_kth_par<5> linear_kp_5(adj);
#define kth_path kth_path_linear
#include "../../../library/graphs/linear_kth_path.hpp"
#undef kth_path
		for (int i = 0; i < 100; i++) {
			int u = get_rand<int>(0, n - 1);
			int v = get_rand<int>(0, n - 1);
			if (u == v || !dsu.same_set(u, v))
				continue;
			auto lca_1 = tl.lca(u, v);
			auto lca_2 = lc.lca(u, v);
			auto lca_3 = lin_lca.lca(u, v);
			assert(lca_1 == lca_2);
			assert(lca_1 == lca_3);
			assert(dist_edges_tree_lift(u, v) == dist_edges_lca_rmq(u, v));
			assert(dist_edges_tree_lift(u, v) == dist_edges_linear_lca(u, v));
			assert(kth_path_tree_lift(u, v, 1) == next_on_path(u, v));
			assert(kth_path_linear(u, v, 1) == next_on_path(u, v));
			if (tl.d[u] > tl.d[v]) swap(u, v);
			auto curr_res = tl.kth_par(v, tl.d[v] - tl.d[u]);
			auto curr_res1 = lad.kth_par(v, tl.d[v] - tl.d[u]);
			assert(curr_res == curr_res1);
			auto curr_res2 = linear_kp_2.kth_par(v, tl.d[v] - tl.d[u]);
			assert(curr_res == curr_res2);
			auto curr_res3 = lin_kp.kth_par(v, tl.d[v] - tl.d[u]);
			assert(curr_res == curr_res3);
			auto curr_res4 = linear_kp_4.kth_par(v, tl.d[v] - tl.d[u]);
			assert(curr_res == curr_res4);
			auto curr_res5 = linear_kp_5.kth_par(v, tl.d[v] - tl.d[u]);
			assert(curr_res == curr_res5);
			assert((u == curr_res) == in_subtree(u, v));
		}
	}
	cout << "Hello World\n";
	return 0;
}
