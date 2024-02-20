#define PROBLEM "https://judge.yosupo.jp/problem/tetration_mod"
#include "../template.hpp"

#include "../../../library/math/tetration_mod.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int t;
	cin >> t;
	while (t--) {
		int a, b, mod;
		cin >> a >> b >> mod;
		cout << tetration(a, b, mod) << '\n';
	}
	return 0;
}
