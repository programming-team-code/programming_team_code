const int mod = 17; /**< must be prime */
vector<int64_t> inv(2, 1), fact(inv), inv_fact(inv);
void grow(int n) {
  assert(n < mod);
  while (ssize(inv) <= n) {
    int i = ssize(inv);
    inv.push_back(mod - (mod / i) * inv[mod % i] % mod);
    fact.push_back(i * fact[i - 1] % mod);
    inv_fact.push_back(inv[i] * inv_fact[i - 1] % mod);
  }
}
/**
 * @param n,k integers with n < mod
 * @returns number of ways to choose k objects out of n
 * @time O(1) amortized
 * @space O(1) amortized
 */
inline int64_t C(int n, int k) {
  if (k < 0 || n < k) return 0;
  grow(n);
  return fact[n] * inv_fact[k] % mod * inv_fact[n - k] % mod;
}
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
