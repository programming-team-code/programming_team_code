#define PROBLEM "https://judge.yosupo.jp/problem/assignment"
#include "../template.hpp"

#include "../../../library/flow/hungarian.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	vector<vector<int64_t>> a(n + 1, vector<int64_t>(n + 1));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
			cin >> a[i][j];
	}
	auto [min_weight, l_to_r] = hungarian(a);
	cout << min_weight << '\n';
	for (int i = 1; i <= n; i++)
		cout << l_to_r[i] - 1 << " ";
	return 0;
}
