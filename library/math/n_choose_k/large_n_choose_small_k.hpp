#pragma once
#include "grow.hpp"
//! n arbitrarily large; k < mod
//! @time O(k) amortized
//! @space O(1) amortized
ll c_small_k(ll n, int k) {
  if (k < 0 || n < k || (n %= mod) < k) return 0;
  grow(k);
  ll res = t[k].inv_fact;
  rep(i, 0, k) res = res * (n - i) % mod;
  return res;
}
