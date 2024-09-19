#pragma once
#include "calc_sieve.hpp"
//! `fac` will equal all prime factors of num, increasing
//! @time O(log(num))
//! @space O(1)
for (int left = num, fac = sieve[left]; left > 1;
     fac = sieve[left /= fac])
