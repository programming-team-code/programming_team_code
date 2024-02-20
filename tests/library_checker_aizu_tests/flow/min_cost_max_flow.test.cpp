#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_6_B"
#include "../template.hpp"

#include "../../../library/flow/min_cost_max_flow.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, f;
	cin >> n >> m >> f;
	mcmf mf(n);
	while (m--) {
		int u, v, cap, cost;
		cin >> u >> v >> cap >> cost;
		mf.add_edge(u, v, cap, cost);
	}
	auto [flow, cost] = mf.get_flow(0, n - 1, f);
	cout << (flow < f ? -1 : cost) << '\n';
	return 0;
}
