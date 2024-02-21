/** @file */
#pragma once
/**
 * @param val an integer
 * @returns 1 iff val is prime
 * @time O(1)
 * @space O(1)
 */
auto is_prime = [&](int val) -> bool {
	return val >= 2 && sieve[val] == val;
};
