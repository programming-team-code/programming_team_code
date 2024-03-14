/** @file */
#pragma once
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
