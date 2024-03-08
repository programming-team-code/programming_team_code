#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"
#include "../../../library/data_structures/uncommon/dsu_restorable.hpp"

#include "../../../library/trees/tree_lift/tree_lift.hpp"

#include "../../../library/trees/lca_rmq/lca_rmq.hpp"

#include "../../../library/trees/linear_lca.hpp"

#include "../../../library/trees/ladder_decomposition/ladder_decomposition.hpp"

#define bit_floor bit_floor_2
#include "../../../library/trees/ladder_decomposition/linear_kth_par.hpp"
#undef bit_floor

#include "../../../library/trees/linear_kth_path.hpp"

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
		LCA lc(adj);
		linear_lca lin_lca(adj);
		ladder lad(adj);
		linear_kth_par<2> linear_kp_2(adj);
		linear_kth_par lin_kp(adj);
		linear_kth_par<4> linear_kp_4(adj);
		linear_kth_par<5> linear_kp_5(adj);
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
			assert(tl.dist_edges(u, v) == lc.dist_edges(u, v));
			assert(tl.dist_edges(u, v) == lin_lca.dist_edges(u, v));
			assert(tl.kth_path(u, v, 1) == lc.next_on_path(u, v));
			assert(kth_path(lin_lca, lin_kp, u, v, 1) == lc.next_on_path(u, v));
			if (tl.d[u] > tl.d[v]) swap(u, v);
			auto res = tl.kth_par(v, tl.d[v] - tl.d[u]);
			assert(res == lad.kth_par(v, tl.d[v] - tl.d[u]));
			assert(res == linear_kp_2.kth_par(v, tl.d[v] - tl.d[u]));
			assert(res == lin_kp.kth_par(v, tl.d[v] - tl.d[u]));
			assert(res == linear_kp_4.kth_par(v, tl.d[v] - tl.d[u]));
			assert(res == linear_kp_5.kth_par(v, tl.d[v] - tl.d[u]));
			assert((u == res) == lc.in_subtree(u, v));
		}
	}
	cout << "Hello World\n";
	return 0;
}