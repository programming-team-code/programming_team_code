/** @file */
#pragma once
/**
 * mobius[i] = 0 iff there exists a prime p s.t. i%(p^2)=0
 * mobius[i] = -1 iff i has an odd number of distinct prime factors
 * mobius[i] = 1 iff i has an even number of distinct prime factors
 * @time O(mx log mx)
 * @space O(mx)
 */
vector<int> mobius(1'000'005);
mobius[1] = 1;
for (int i = 1; i < ssize(mobius); i++)
  for (int j = i + i; j < ssize(mobius); j += i)
    mobius[j] -= mobius[i];
