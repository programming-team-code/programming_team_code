/** @file */
#pragma once
const int mod = 998'244'353;
/**
 * @see https://github.com/kth-competitive-programming/kactl /blob/main/content/number-theory/ModPow.h
 * @param b base
 * @param e exponent
 * @returns (b^e)%mod, 1 for 0^0.
 * @time O(log e)
 * @space O(1)
 */
int64_t bin_exp(int64_t b, int64_t e) {
	assert(0 <= e);
	auto res = 1LL;
	if ((b %= mod) < 0) b += mod;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) res = res * b % mod;
	return res;
}
