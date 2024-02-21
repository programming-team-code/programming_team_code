#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/8/ITP2/all/ITP2_11_C"
#include "../template.hpp"

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
	cout << 0 << ':' << '\n';
	vector<int> sb_msks;
	{
#include "../../../library/loops/submasks.hpp"
		sb_msks.push_back(submask);
	}
	reverse(begin(sb_msks), end(sb_msks));
	for (auto submask : sb_msks) {
		cout << submask << ':';
		for (int bit = 0; bit < n; bit++) {
			if ((submask >> bit) & 1)
				cout << ' ' << bit;
		}
		cout << '\n';
	}
	return 0;
}
