#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_C"
#include "../template.hpp"

#include "../../../library/math/prime_sieve/calc_linear_sieve.hpp"

#include "../../../kactl/content/number-theory/MillerRabin.h"

inline bool is_prime(int val) {
	assert(val < mx_n && sieve[1] == 1);
	return val >= 2 && sieve[val] == val;
}

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

int main() {
	cin.tie(0)->sync_with_stdio(0);
	vector<int> primes = calc_sieve();
	for (int i = 1; i < mx_n; i++)
		assert(isPrime(i) == is_prime(i));
	for (int p : primes)
		assert(isPrime(p));
	assert(ssize(primes) == 168);
	int n;
	cin >> n;
	map<int, int> prime_to_max_exponent;
	while (n--) {
		int val;
		cin >> val;
		map<int, int> curr;
		{
			int prev_prime = -1;
			for (auto prime_factor : get_prime_factors(val)) {
				assert(prime_factor >= prev_prime);
				prev_prime = prime_factor;
				curr[prime_factor]++;
			}
		}
		for (auto [p, e] : curr)
			prime_to_max_exponent[p] = max(prime_to_max_exponent[p], e);
	}
	int res = 1;
	for (auto [p, e] : prime_to_max_exponent) {
		while (e--)
			res *= p;
	}
	cout << res << '\n';
	return 0;
}
