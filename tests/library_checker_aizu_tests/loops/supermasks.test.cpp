#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/8/ITP2/all/ITP2_11_B"
#include "../template.hpp"

#include "../../../library/loops/supermasks.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, k;
	cin >> n >> k;
	int mask = 0;
	for (int i = 0; i < k; i++) {
		int bit;
		cin >> bit;
		mask |= 1 << bit;
	}
	vector<int> sup_msks;
	auto f = [&](int supermask) {
		sup_msks.push_back(supermask);
	};
	supermasks(mask, n, f);
	sort(begin(sup_msks), end(sup_msks));
	for (auto supermask : sup_msks) {
		cout << supermask << ':';
		for (int bit = 0; bit < n; bit++) {
			if ((supermask >> bit) & 1)
				cout << ' ' << bit;
		}
		cout << '\n';
	}
	return 0;
}
