#define PROBLEM "https://judge.yosupo.jp/problem/predecessor_problem"
#include "../template.hpp"

#include "../../../library/data_structures/bit_uncommon/lower_bound.hpp"
#include "../../../library/data_structures/seg_tree_uncommon/lower_bound.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q;
	string s;
	cin >> n >> q >> s;
	vector<int> init(n);
	for (int i = 0; i < n; i++)
		init[i] = s[i] - '0';
	BIT<int> bit(init);
	seg_tree st(init);
	while (q--) {
		int type, k;
		cin >> type >> k;
		if (type == 0) {
			if (bit.query(k, k + 1) == 0) {
				bit.update(k, 1);
				st.update(k, k + 1, 1);
			}
		} else if (type == 1) {
			if (bit.query(k, k + 1) == 1) {
				bit.update(k, -1);
				st.update(k, k + 1, -1);
			}
		} else if (type == 2) {
			int res = bit.query(k, k + 1);
			auto res_st = st.query(k, k + 1);
			assert(res == res_st);
			cout << res << '\n';
		} else if (type == 3) {
			if (bit.query(k, k + 1) == 1) {
				cout << k << '\n';
				continue;
			}
			int order = bit.query(k);
			int res = lower_bound(bit, order + 1);
			auto res_st = lower_bound(st, order + 1);
			assert(res == res_st);
			if (res == n + 1)
				res = 0;
			cout << res - 1 << '\n';
		} else {
			if (bit.query(k, k + 1) == 1) {
				cout << k << '\n';
				continue;
			}
			int order = bit.query(k);
			int res = lower_bound(bit, order);
			auto res_st = lower_bound(st, order);
			assert(res == res_st);
			cout << res - 1 << '\n';
		}
	}
	return 0;
}
