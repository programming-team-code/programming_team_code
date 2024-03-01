#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"

#include "../../../library/data_structures/bit_uncommon/rupq.hpp"
#include "../../../library/data_structures/bit_uncommon/rurq.hpp"
#include "../../../library/data_structures/bit_uncommon/lower_bound.hpp"
#include "../../../library/data_structures/seg_tree_uncommon/lower_bound.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q;
	cin >> n >> q;
	vector<int64_t> arr(n);
	vector<int> arr_int(n);
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
		arr_int[i] = int(arr[i]);
	}
	BIT<int64_t> bit(arr);
	seg_tree st(arr_int);
	bit_rurq<int64_t> bit_rr(arr);
	vector<int64_t> suf_sum(n);
	partial_sum(rbegin(arr), rend(arr), rbegin(suf_sum));
	bit_rupq<int64_t> bit_i(suf_sum);
	for (int i = 0; i < n; i++) {
		auto curr_1 = bit.query(i, i + 1);
		assert(arr[i] == curr_1);
		auto curr_2 = bit_i.get_index(i);
		auto curr_3 = bit.query(i, n);
		assert(curr_2 == curr_3);
		auto curr_4 = bit_i.get_index(i);
		assert(curr_4 == suf_sum[i]);
	}
	while (q--) {
		int type;
		cin >> type;
		if (type == 0) {
			int p, x;
			cin >> p >> x;
			bit.update(p, x);
			st.update(p, p + 1, x);
			bit_rr.update(p, p + 1, x);
			bit_i.update(0, p + 1, x);
		} else {
			int l, r;
			cin >> l >> r;
			int64_t res = bit.query(l, r);
			{
				int64_t bit_i_result = bit_i.get_index(l);
				if (r < n) bit_i_result -= bit_i.get_index(r);
				assert(res == bit_i_result);
			}
			auto curr_res = bit_rr.query(l, r);
			assert(res == curr_res);
			cout << res << '\n';
		}
		auto sum = get_rand<int64_t>(0LL, (int64_t)(1e12));
		int pos_bit = lower_bound(bit, sum);
		int pos_st = lower_bound(st, sum);
		assert(pos_bit == pos_st);
	}
	return 0;
}
