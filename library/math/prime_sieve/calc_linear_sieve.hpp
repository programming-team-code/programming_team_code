/** @file */
#pragma once
/**
 * @time O(mx)
 * @space O(mx)
 */
vector<int> sieve(1001) /**< min prime factor */, primes;
iota(begin(sieve), end(sieve), 0);
for (int i = 2; i < ssize(sieve); i++) {
  if (sieve[i] == i) primes.push_back(i);
  for (int prime : primes) {
    if (prime * i >= ssize(sieve)) break;
    sieve[prime * i] = prime;
    if (i % prime == 0) break;
  }
}
