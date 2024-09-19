#pragma once
#include "calc_sieve.hpp"
//! @time O(1)
//! @space O(1)
auto is_prime = [&](int num) -> bool {
  return num >= 2 && sieve[num] == num;
};
