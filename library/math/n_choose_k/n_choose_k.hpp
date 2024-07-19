/** @file */
#pragma once
const int mod = 17; /**< must be prime */
struct comb {
  ll inv = 1, fact = 1, inv_fact = 1;
};
vector<comb> t(2);
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
  while (sz(t) <= n) {
    int i = sz(t);
    ll inv = mod - (mod / i) * t[mod % i].inv % mod;
    t.push_back({inv, i * t[i - 1].fact % mod, inv * t[i - 1].inv_fact % mod});
  }
  return t[n].fact * t[k].inv_fact % mod * t[n - k].inv_fact % mod;
}
