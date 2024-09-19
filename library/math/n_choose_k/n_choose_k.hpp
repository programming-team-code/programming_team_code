#pragma once
#include "grow.hpp"
//! n,k < mod
//! @time O(1) amortized
//! @space O(1) amortized
// NOLINTNEXTLINE(readability-identifier-naming)
ll C(int n, int k) {
  if (k < 0 || n < k) return 0;
  grow(n);
  return t[n].fact * t[k].inv_fact % mod *
    t[n - k].inv_fact % mod;
}
