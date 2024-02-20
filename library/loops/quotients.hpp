/** @file */
#pragma once
/**
 * @see https://github.com/tfg50/Competitive-Programming/ blob/master/Biblioteca/Math/DivisionTrick.cpp
 *
 * i-th iteration gives an interval [le_i, ri_i], we have:
 *     - for all i in [le_i, ri_i]: n / i has the same value
 *     - le_0 = 1
 *     - ri_last = n
 *     - ri_i + 1 = le_(i+1)
 *
 * @param n,f number and helper function
 * @time O(sqrt(n))
 * @space O(1)
 */
template <class F> void quotients(int64_t n, F f) {
	for (int64_t le = 1, ri; le <= n; le = ri + 1) {
		ri = n / (n / le);
		f(le, ri);
	}
}
