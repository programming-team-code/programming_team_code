/** @file */
#pragma once
#include "n_choose_k.hpp"
const int mod = 17; /**< must be prime */
/**
 * @param n arbitrarily large integer
 * @param k integer with k < mod
 * @returns number of ways to choose k objects out of n
 * @time O(k)
 * @space O(1) amortized
 */
inline ll c_small_k(ll n, int k) {
  if (k < 0 || n < k || (n %= mod) < k) return 0;
  C(k, k);
  ll res = inv_fact[k];
  rep(i, 0, k) res = res * (n - i) % mod;
  return res;
}
