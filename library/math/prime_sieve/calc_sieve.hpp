/** @file */
#pragma once
/**
 * @time O(mx * log(log mx))
 * @space O(mx)
 */
vector<int> sieve(1001); /**< min prime factor */
iota(begin(sieve), end(sieve), 0);
for (int i = 2; i * i < ssize(sieve); i++)
  if (sieve[i] == i)
    for (int j = i * i; j < ssize(sieve); j += i)
      sieve[j] = min(sieve[j], i);
