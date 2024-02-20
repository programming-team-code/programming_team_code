/** @file */
#pragma once
#include "../bit.hpp"
/**
 * @see https://github.com/dacin21/dacin21_codebook /blob/master/trees/wavelet_matrix_updates.cpp
 *
 * space efficient boolean array with range sum query, and point update
 * note `>> 6` is the same as `/ 64`
 * note `& 63` is the same as `% 64`
 */
struct bool_bit {
	int n;
	vector<uint64_t> mask;
	BIT<int> presum;
	/**
	 * @param a boolean array
	 * @time O(n)
	 * @space O(n / 64)
	 */
	bool_bit(const vector<bool>& a) : n(ssize(a)), mask(n / 64 + 1) {
		vector<int> init((n + 63) / 64);
		for (int i = 0; i < n; i++) {
			mask[i >> 6] |= (uint64_t(a[i]) << (i & 63));
			init[i >> 6] += a[i];
		}
		presum = {init};
	}
	/**
	 * @param i defines range [0, i)
	 * @returns a[0] + a[1] + ... + a[i - 1]
	 * @time O(log(n / 64))
	 * @space O(1)
	 */
	inline int popcount(int i) {
		assert(0 <= i && i <= n);
		return presum.sum(i >> 6) + __builtin_popcountll(mask[i >> 6] & ((1ULL << (i & 63)) - 1));
	}
	/**
	 * @param le,ri defines range [le, ri)
	 * @returns a[le] + a[le + 1] + ... + a[ri - 1]
	 * @time O(log(n / 64))
	 * @space O(1)
	 */
	inline int popcount(int le, int ri) {
		assert(le <= ri);
		return popcount(ri) - popcount(le);
	}
	/**
	 * @param i index
	 * @returns 1 iff index i is active
	 * @time O(1)
	 * @space O(1)
	 */
	inline bool on(int i) {
		assert(0 <= i && i < n);
		return (mask[i >> 6] >> (i & 63)) & 1;
	}
	/**
	 * @param i index
	 * @param new_val we want to set a[i] = new_val
	 * @time O(log(n / 64))
	 * @space O(1)
	 */
	void set(int i, bool new_val) {
		assert(0 <= i && i < n);
		if (on(i) != new_val) {
			mask[i >> 6] ^= 1ULL << (i & 63);
			presum.update(i >> 6, new_val ? 1 : -1);
		}
	}
};
