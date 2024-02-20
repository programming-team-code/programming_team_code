/** @file */
#pragma once
const int mx_n = 1001;
int sieve[mx_n]; /**< for val >= 2, sieve[val] = smallest prime p such that val % p == 0 */
/**
 * @returns a list of all of the primes < mx_n
 * @time O(mx_n)
 * @space O(mx_n)
 */
vector<int> calc_sieve() {
	iota(begin(sieve), end(sieve), 0);
	vector<int> primes;
	for (int i = 2; i < mx_n; i++) {
		if (sieve[i] == i)
			primes.push_back(i);
		for (int prime : primes) {
			int prod = prime * i;
			if (prod >= mx_n)
				break;
			sieve[prod] = prime;
			if (i % prime == 0)
				break;
		}
	}
	return primes;
}
