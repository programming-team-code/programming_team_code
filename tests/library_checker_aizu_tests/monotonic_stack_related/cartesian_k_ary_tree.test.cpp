#define PROBLEM "https://judge.yosupo.jp/problem/cartesian_tree"
#include "../template.hpp"
#include "../mono_st_asserts.hpp"

#include "../../../library/monotonic_stack/cartesian_k_ary_tree.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) cin >> a[i];
	mono_st_asserts(a);
	auto le = mono_st(a, less_equal()), ri = mono_range(le), p = cart_k_ary_tree(a, ri);
	assert(*min_element(begin(p), end(p)) >= 0);
	assert(*max_element(begin(p), end(p)) == n);
	vector<int> a_neg(n);
	transform(begin(a), end(a), begin(a_neg), [](int x) {return -x;});
	auto le_neg = mono_st(a_neg, greater_equal()), ri_neg = mono_range(le_neg), p_neg = cart_k_ary_tree(a_neg, ri_neg);
	assert(ri == ri_neg);
	assert(p == p_neg);
	for (int i = 0; i < n; i++) {
		if (p[i] != n) assert(a[p[i]] < a[i]); //because distinct numbers
		cout << (p[i] == n ? i : p[i]) << " ";
	}
	return 0;
}
