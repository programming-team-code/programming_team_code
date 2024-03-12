#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"

#include "../../../library/contest/random.hpp"
#include "../../../library/data_structures/bit.hpp"
#include "../../../library/data_structures/bit_uncommon/lower_bound.hpp"
#include "../../../library/data_structures/seg_tree.hpp"

const int n = 100'000;
inline int rv(int i) { return n - i - 1; }

int main() {
	cin.tie(0)->sync_with_stdio(0);
	BIT<int> bit(n);
	seg_tree seg(n), rev(n);
	vector<int> a(n);
	for (int q = 0; q < 100'000; q++) {
		int i = get_rand(0, n - 1);
		bit.update(i, -a[i]);
		seg.update(i, i + 1, -a[i]);
		rev.update(rv(i), rv(i) + 1, -a[i]);
		a[i] ^= 1;
		bit.update(i, a[i]);
		seg.update(i, i + 1, a[i]);
		rev.update(rv(i), rv(i) + 1, a[i]);
		int le = get_rand(0, n - 1);
		int ri = get_rand(le + 1, n);
		assert(bit.query(0, le) == seg.query(0, le));
		int k = bit.query(0, le);
		int pos = min(bit.lower_bound(k + 1) - 1, ri);
		auto f = [](int64_t x, int _le, int _ri) { return x > 0; };
		assert(pos == seg.find_first(le, ri, f));
		assert(pos == rv(rev.find_last(rv(ri - 1), rv(le) + 1, f)));
	}
	cout << "Hello World\n";
	return 0;
}
