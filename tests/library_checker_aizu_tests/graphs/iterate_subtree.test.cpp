#define PROBLEM "https://judge.yosupo.jp/problem/lca"
#include "../template.hpp"

#include "../../../library/graphs/lca_rmq/lca_rmq.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q;
	cin >> n >> q;
	vector<vector<int>> adj(n);
	for (int i = 1; i < n; i++) {
		int par;
		cin >> par;
		adj[par].push_back(i);
	}
	LCA lc(adj);
#include "../../../library/graphs/lca_rmq/in_subtree.hpp"
	{
		vector<int> cnt_small_iterated(n), cnt_big_iterated(n);
		for (int i = 0; i < n; i++) {
			if (empty(adj[i])) continue;
			int big_ch_idx = int(max_element(begin(adj[i]), end(adj[i]), [&](int x, int y) {return lc.sub_sz[x] < lc.sub_sz[y];}) - begin(adj[i]));
			for (int j = 0; j < ssize(adj[i]); j++) {
				int u = adj[i][j];
				assert(lc.sub_sz[u] <= lc.sub_sz[adj[i][big_ch_idx]]);
				if (j == big_ch_idx) {
					int le = lc.in[u];
					int ri = lc.in[u] + lc.sub_sz[u];
					cnt_big_iterated[le]++;
					if (ri < n) cnt_big_iterated[ri]--;
					continue;
				}
#include "../../../library/graphs/lca_rmq/iterate_subtree.hpp"
				assert(lc.d[u] <= lc.d[v]);
				assert(in_subtree(u, v));
				cnt_small_iterated[v]++;
			}
		}
	}
	partial_sum(begin(cnt_big_iterated), end(cnt_big_iterated), begin(cnt_big_iterated));
	for (int i = 0; i < n; i++) {
		//at each merge (small to large), subtree size doubles or more
		//how many doubles until it reaches n?
		//sub_sz * 2^k ~= n
		//2^k ~= n / sub_sz
		//k ~= __lg(n / sub_sz)
		assert(cnt_small_iterated[i] <= __lg(n / lc.sub_sz[i]));
		assert(cnt_small_iterated[i] + cnt_big_iterated[lc.in[i]] == lc.d[i]);
	}
}
while (q--) {
	int u, v;
	cin >> u >> v;
	cout << lc.lca(u, v) << '\n';
}
}
