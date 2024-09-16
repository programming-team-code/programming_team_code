//! @file
#pragma once
#include "grow.hpp"
//! @param n,k integers with n < mod
//! @returns number of ways to choose k objects out
//! of n
//! @time O(1) amortized
//! @space O(1) amortized
// NOLINTNEXTLINE(readability-identifier-naming)
ll C(int n, int k) {
  if (k < 0 || n < k) return 0;
  grow(n);
  return t[n].fact * t[k].inv_fact % mod *
         t[n - k].inv_fact % mod;
}
