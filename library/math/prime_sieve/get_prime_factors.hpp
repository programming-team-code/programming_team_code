/** @file */
#pragma once
#include "calc_sieve.hpp"
/**
 * @param val an integer
 * @returns all prime factors of val (sorted)
 * @time O(log(val))
 * @space this function allocates/returns a O(log(val)) vector
 */
vector<int> get_prime_factors(int val) {
	assert(val < mx_n && sieve[1] == 1);
	vector<int> factors;
	while (val > 1) {
		int p = sieve[val];
		factors.push_back(p);
		val /= p;
	}
	return factors;
}
