//! @time O(mx)
//! @space O(mx)
vector<int> primes, sieve(1001); //!< min prime factor
iota(begin(sieve), end(sieve), 0);
for (int i = 2; i < ((int)size(sieve)); i++) {
  if (sieve[i] == i) primes.push_back(i);
  for (int prime : primes) {
    if (prime * i >= (int)size(sieve)) break;
    sieve[prime * i] = prime;
    if (i % prime == 0) break;
  }
}
