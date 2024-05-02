/** @file */
#pragma once
const ll mod = 17; /**< must be prime */
/**
 * @param n arbitrarily large integer
 * @param k integer with k < mod
 * @returns number of ways to choose k objects out of n
 * @time O(k)
 * @space O(k)
 */
inline ll c_small_k(ll n, int k) {
  if (k < 0 || n < k || (n %= mod) < k) return 0;
  vector<ll> inv(k + 1, 1);
  rep(i, 2, k + 1) inv[i] = mod - (mod / i) * inv[mod % i] % mod;
  ll res = 1;
  rep(i, 1, k + 1) res = res * (n - k + i) % mod * inv[i] % mod;
  return res;
}
