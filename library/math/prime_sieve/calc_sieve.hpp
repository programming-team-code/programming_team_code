#pragma once
//! @time O(mx * log(log mx))
//! @space O(mx)
vi sieve(1001); //!< min prime factor
iota(all(sieve), 0);
for (int i = 2; i * i < sz(sieve); i++)
  if (sieve[i] == i)
    for (int j = i * i; j < sz(sieve); j += i)
      sieve[j] = min(sieve[j], i);
