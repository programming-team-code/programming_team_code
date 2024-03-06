#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"
#include "../template.hpp"
#include "../mono_st_asserts.hpp"

#include "../../../library/data_structures/rmq.hpp"
#include "../../../library/data_structures/uncommon/disjoint_rmq.hpp"
#include "../../../library/data_structures/uncommon/linear_rmq.hpp"

int mn(int x, int y) {
	return min(x, y);
}

bool my_cmp(int x, int y) {
	return x < y;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	{
		RMQ rmq_without_template(vector<int>(), mn);
		disjoint_rmq disjoint_rmq_without_template(vector<int>(), mn);
		linear_rmq lin_rmq_without_template(vector<int>(), my_cmp);
	}
	int n, q;
	cin >> n >> q;
	vector<int> a(n);
	for (int i = 0; i < n; i++) cin >> a[i];
	mono_st_asserts(a);
	RMQ rmq(a, [](auto x, auto y) {return min(x, y);});
	disjoint_rmq dis_rmq(a, [](auto x, auto y) {return min(x, y);});
	linear_rmq lin_rmq(a, less());
	while (q--) {
		int le, ri;
		cin >> le >> ri;
		int idx_min = lin_rmq.query_idx(le, ri - 1);
		assert(a[idx_min] == rmq.query(le, ri));
		assert(a[idx_min] == dis_rmq.query(le, ri));
		cout << a[idx_min] << '\n';
	}
}
