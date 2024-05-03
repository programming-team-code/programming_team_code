/** @file */
#pragma once
#include "mod_int.hpp"
/**
 * @see https://github.com/kth-competitive-programming/kactl /blob/main/content/number-theory/ModPow.h
 * @param b base
 * @param e exponent
 * @returns (b^e)%mod, 1 for 0^0.
 * @time O(log e)
 * @space O(1)
 */
mint mpow(mint b, ll e) {
  assert(e >= 0);
  mint res = 1;
  for (; e; e /= 2, b = b * b)
    if (e & 1) res = res * b;
  return res;
}
