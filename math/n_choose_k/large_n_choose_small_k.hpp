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
 * @param n arbitrarily large integer
 * @param k integer with k < mod
 * @returns number of ways to choose k objects out of n
 * @time O(k)
 * @space O(1) ammortized
 */
inline int64_t c_small_k(int64_t n, int k) {
  if (k < 0 || n < k || (n %= mod) < k) return 0;
  grow(k);
  auto res = inv_fact[k];
  for (int i = n; i > n - k; i--) res = res * i % mod;
  return res;
}
