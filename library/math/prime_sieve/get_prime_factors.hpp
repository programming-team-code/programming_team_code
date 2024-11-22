#pragma once
#include "calc_sieve.hpp"
//! `p` will be all prime factors of num, increasing
//! @time O(log(num))
//! @space O(1)
for (int cpy = num, p; (p = sieve[cpy]) > 1; cpy /= p) 