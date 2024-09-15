//! @file
#pragma once
#include "monotonic_stack.hpp"
//! @code{.cpp}
//!     vector<ll> a;
//!     auto le = mono_st(a, less()), ri = mono_range(le); // greater(), less_equal(), greater_equal()
//! @endcode
//! @param le monotonic stack array of a
//! @returns vector ri where ri[i] = min index such that: i < ri[i] and
//!          !cmp(a[i], a[ri[i]]). If no index exists, ri[i] = n
//! @time O(n)
//! @space a O(n) vector is allocated and returned
vi mono_range(const vi& le) {
  vi ri(sz(le), sz(le));
  rep(i, 0, sz(le)) for (int j = i - 1; j != le[i]; j = le[j]) ri[j] = i;
  return ri;
}
