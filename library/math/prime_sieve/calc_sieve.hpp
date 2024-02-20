/** @file */
#pragma once
const int mx_n = 1001;
int sieve[mx_n]; /**< for val >= 2, sieve[val] = smallest prime p such that val % p == 0 */
/**
 * @time O(mx_n * log(log mx_n))
 * @space O(mx_n) for `sieve` vector
 */
void calc_sieve() {
	iota(begin(sieve), end(sieve), 0);
	for (int i = 2; i * i < mx_n; i++)
		if (sieve[i] == i)
			for (int j = i * i; j < mx_n; j += i)
				sieve[j] = min(sieve[j], i);
}
