/** @file */
#pragma once
#include "factorial.hpp"
/**
 * @param n,k integers with n < mod
 * @returns number of ways to choose k objects out of n
 * @time O(1) amortized
 * @space O(1) amortized
 */
// NOLINTNEXTLINE(readability-identifier-naming)
inline int64_t C(int n, int k) {
  if (k < 0 || n < k) return 0;
  grow(n);
  return fact[n] * inv_fact[k] % mod * inv_fact[n - k] % mod;
}
