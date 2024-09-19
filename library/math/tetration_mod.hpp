#pragma once
#include "totient.hpp"
//! https://cp-algorithms.com/algebra/phi-function.html#generalization
//! Let t = totient(mod).
//! If log2(mod) <= e then
//!   (b^e)%mod == (b^(t+(e%t)))%mod
//!
//! returns b ^ (b ^ (... ^ b))) % mod, where
//!   the height of the tower is e.
//
//! @time O(sqrt(mod) * log(mod))
//! @space O(log(mod))
ll bin_exp(ll b, ll e, int mod) {
  ll res = 1;
  if ((b %= mod) < 0) b += mod;
  for (; e; b = b * b % mod, e /= 2)
    if (e & 1) res = res * b % mod;
  return res;
}
ll tetration(ll b, ll e, int mod) {
  if (mod == 1) return 0;
  if (b == 0) return (e + 1) % 2 % mod;
  if (b == 1 || e == 0) return 1;
  if (e == 1) return b % mod;
  if (b == 2 && e == 2) return 4 % mod;
  if (b == 2 && e == 3) return 16 % mod;
  if (b == 3 && e == 2) return 27 % mod;
  int t = totient(mod);
  ll exp = tetration(b, e - 1, t);
  return bin_exp(b, exp + t, mod);
}
