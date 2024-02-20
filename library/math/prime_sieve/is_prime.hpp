/** @file */
#pragma once
#include "calc_sieve.hpp"
/**
 * @param val an integer
 * @returns 1 iff val is prime
 * @time O(1)
 * @space O(1)
 */
inline bool is_prime(int val) {
	assert(val < mx_n && sieve[1] == 1);
	return val >= 2 && sieve[val] == val;
}
