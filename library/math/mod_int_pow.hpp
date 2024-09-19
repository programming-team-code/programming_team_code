#pragma once
#include "mod_int.hpp"
//! https://github.com/kth-competitive-programming/kactl/blob/main/content/number-theory/ModPow.h
//! returns (b^e)%mod, 1 for 0^0.
//! @time O(log e)
//! @space O(1)
mint mpow(mint b, ll e) {
  mint res = 1;
  for (; e; e /= 2, b = b * b)
    if (e & 1) res = res * b;
  return res;
}
