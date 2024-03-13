#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"
#include "../template.hpp"

#include "../../../library/contest/random.hpp"
#include "../../../library/data_structures/uncommon/dsu_bipartite.hpp"

vector<bool> bipartite_check(const vector<vector<int>>& adj) {
	int n = ssize(adj);
	vector<bool> is_bi(n);
	vector<int> color(n, -1);
	for (int s = 0; s < n; s++) {
		if (color[s] != -1) continue;
		color[s] = 0;
		vector<int> q{s};
		bool is_bipartite = 1;
		for (int fr = 0; fr < ssize(q); fr++) {
			int u = q[fr];
			for (int v : adj[u]) {
				if (color[v] == -1) {
					color[v] = color[u] ^ 1;
					q.push_back(v);
				} else
					is_bipartite &= color[v] != color[u];
			}
		}
		for (int u : q) is_bi[u] = is_bipartite;
	}
	return is_bi;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q;
	cin >> n >> q;
	dsu_bipartite dsu(n);
	vector<vector<int>> adj(n);
	auto check = [&]() {
		vector<bool> is_bi = bipartite_check(adj);
		for (int s = 0; s < n; s++) assert(dsu.is_bipartite(s) == is_bi[s]);
	};
	for (int i = 0; i < q; i++) {
		int t, u, v;
		cin >> t >> u >> v;
		if (t == 0) {
			dsu.join(u, v);
			adj[u].push_back(v);
			adj[v].push_back(u);
		} else
			cout << dsu.same_set(u, v) << '\n';
		if (get_rand<int>(0, 20'000) == 0) check();
	}
	check();
	return 0;
}