/** @file */
#pragma once
/**
 * `fac` will equal all prime factors of val, increasing
 * @param val positive integer
 * @time O(log(val))
 * @space O(1)
 */
for (int left = val, fac = sieve[left]; left > 1; fac = sieve[left /= fac])
