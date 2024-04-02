/** @file */
#pragma once
/**
 * @time O(mx)
 * @space O(mx)
 */
vi sieve(1001) /**< min prime factor */, primes;
iota(all(sieve), 0);
rep(i, 2, sz(sieve)) {
  if (sieve[i] == i) primes.push_back(i);
  for (int prime : primes) {
    if (prime * i >= sz(sieve)) break;
    sieve[prime * i] = prime;
    if (i % prime == 0) break;
  }
}
