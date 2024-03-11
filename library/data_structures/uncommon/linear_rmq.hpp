/** @file */
#pragma once
#include "../../monotonic_stack/monotonic_range.hpp"
#include "../../monotonic_stack/cartesian_binary_tree.hpp"
inline int bit_floor(unsigned x) {return x ? 1 << __lg(x) : 0;}
/**
 * @see On Finding Lowest Common Ancestors: Simplification and Parallelization
 * by Baruch Schieber, Uzi Vishkin, April 1987
 */
template <class T, class F> struct linear_rmq {
	int n;
	F cmp;
	vector<T> a;
	vector<int> head;
	vector<unsigned> in_label, ascendant;
	/**
	 * @code{.cpp}
	       vector<int64_t> a(n);
	       linear_rmq rmq(a, less()); // right-most min
	       linear_rmq rmq(a, less_equal()); // left-most min
	       linear_rmq rmq(a, greater()); // right-most max
	       linear_rmq rmq(a, greater_equal()); // left-most max
	 * @endcode
	 * @param a_a,a_cmp array and a compare operator
	 * @time O(n)
	 * @space O(n)
	 */
	linear_rmq(const vector<T>& a_a, F a_cmp) : n(ssize(a_a)), cmp(a_cmp), a(a_a), head(n + 1), in_label(n), ascendant(n) {
		vector<int> le(mono_st(a, cmp)), ri(mono_range(le)), p(cart_binary_tree(le));
		for (int i = 0; i < n; i++)
			in_label[i] = ri[i] & -bit_floor(unsigned((le[i] + 1) ^ ri[i]));
		for (int i = 0; i < n; i++)
			if (p[i] == -1 || in_label[p[i]] != in_label[i]) {
				head[in_label[i]] = p[i];
				int to_add = in_label[i] & -in_label[i];
				ascendant[le[i] + 1] += to_add;
				if (ri[i] < n) ascendant[ri[i]] -= to_add;
			}
		partial_sum(begin(ascendant), end(ascendant), begin(ascendant));
	}
	inline int lift(int u, unsigned j) {
		auto k = bit_floor(ascendant[u] ^ j);
		return k == 0 ? u : head[(in_label[u] & -k) | k];
	}
	/**
	 * @param le,ri defines range [min(le, ri), max(le, ri)]
	 * @returns index of min/max of range
	 * @time O(1)
	 * @space O(1)
	 */
	inline int query_idx(int le, int ri) {
		auto [x, y] = minmax(in_label[le], in_label[ri]);
		auto j = ascendant[le] & ascendant[ri] & -bit_floor((x - 1) ^ y);
		return cmp(a[le = lift(le, j)], a[ri = lift(ri, j)]) ? le : ri;
	}
};
