/** @file */
#pragma once
#include "n_choose_k.hpp"
/**
 * @param n,k arbitrarily large integers; n, k >= mod is ok
 * @returns number of ways to choose k objects out of n
 * @time O(log(k)) amortized
 * @space O(1) amortized
 */
inline int64_t lucas(int64_t n, int64_t k) {
  if (k < 0 || n < k) return 0;
  int64_t res = 1;
  for (; k && k < n && res; n /= mod, k /= mod)
    res = res * C(n % mod, k % mod) % mod;
  return res;
}
