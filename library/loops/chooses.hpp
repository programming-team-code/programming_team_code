//! @file
#pragma once
#include "next_subset.hpp"
//! loop over all submasks of 2^n-1 with k bits set, increasing
//! @time O(n choose k)
//! @space O(1)
for (int mask = (1 << k) - 1; mask < (1 << n);
     mask = next_subset(mask))
