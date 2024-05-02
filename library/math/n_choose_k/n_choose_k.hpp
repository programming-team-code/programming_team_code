/** @file */
#pragma once
const ll mod = 17; /**< must be prime */
vector<ll> inv(2, 1), fact(inv), inv_fact(inv);
/**
 * @param n,k integers with n < mod
 * @returns number of ways to choose k objects out of n
 * @time O(1) amortized
 * @space O(1) amortized
 */
// NOLINTNEXTLINE(readability-identifier-naming)
inline ll C(int n, int k) {
  assert(n < mod);
  if (k < 0 || n < k) return 0;
  while (sz(inv) <= n) {
    int i = sz(inv);
    inv.push_back(mod - (mod / i) * inv[mod % i] % mod);
    fact.push_back(i * fact[i - 1] % mod);
    inv_fact.push_back(inv[i] * inv_fact[i - 1] % mod);
  }
  return fact[n] * inv_fact[k] % mod * inv_fact[n - k] % mod;
}
