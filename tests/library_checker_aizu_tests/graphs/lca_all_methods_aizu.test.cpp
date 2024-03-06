#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C"
#include "../template.hpp"

#include "../../../library/graphs/tree_lift/tree_lift.hpp"

#include "../../../library/graphs/linear_lca/linear_lca.hpp"

#include "../../../library/graphs/lca_rmq/lca_rmq.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	vector<vector<int>> adj(n);
	for (int i = 0; i < n; i++) {
		int k;
		cin >> k;
		adj[i].resize(k);
		for (int& child : adj[i])
			cin >> child;
	}
	tree_lift tl(adj);
	LCA lc(adj);
#include "../../../library/graphs/lca_rmq/in_subtree.hpp"
	linear_lca lin_lca(adj);
	for (int i = 0; i < n; i++) {
		auto curr_1 = tl.get_lca(i, i);
		assert(curr_1 == i);
		auto curr_2 = lc.get_lca(i, i);
		assert(curr_2 == i);
		auto curr_3 = lin_lca.get_lca(i, i);
		assert(curr_3 == i);
		assert(lc.in[lc.order[i]] == i && lc.order[lc.in[i]] == i);
	}
	int q;
	cin >> q;
	while (q--) {
		int u, v;
		cin >> u >> v;
		int curr_lca = tl.get_lca(u, v);
		auto curr_1 = lc.get_lca(u, v);
		assert(curr_lca == curr_1);
		auto curr_2 = lin_lca.get_lca(u, v);
		assert(curr_lca == curr_2);
		assert((curr_lca == u) == in_subtree(u, v));
		assert((curr_lca == v) == in_subtree(v, u));
		cout << curr_lca << '\n';
	}
}
