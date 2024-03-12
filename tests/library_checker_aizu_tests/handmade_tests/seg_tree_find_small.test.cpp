#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"

#include "../../../library/contest/random.hpp"
#include "../../../library/data_structures/seg_tree.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	for (int iters = 0; iters < 100; ++iters) {
		int n = 1'000;
		seg_tree seg(n);
		vector<int> a(n);
		for (int q = 0; q < 1'000; q++) {
			int i = get_rand(0, n - 1);
			seg.update(i, i + 1, -a[i]);
			a[i] ^= 1;
			seg.update(i, i + 1, a[i]);
			int le = get_rand(0, n - 1);
			int ri = get_rand(le + 1, n);
			int first_zero = ri, last_zero = le - 1;
			for (int pos = le; pos < ri; pos++) {
				if (a[pos] == 0) {
					first_zero = min(first_zero, pos);
					last_zero = max(last_zero, pos);
				}
			}
			auto f = [](int64_t x, int le, int ri) { return x < ri - le; };
			assert(first_zero == seg.find_first(le, ri, f));
			assert(last_zero == seg.find_last(le, ri, f));
		}
	}
	cout << "Hello World\n";
	return 0;
}
