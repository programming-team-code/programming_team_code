#pragma once
#include "monotonic_stack.hpp"
//! @code
//!   auto mono_le2 = mono_st(a, less());
//!   auto mono_ri2 = mono_range(mono_le2);
//!   // less_equal(), greater(), greater_equal()
//! @endcode
//! when cmp == less():
//!   a[mono_le2[i]] < a[i] >= a[mono_ri2[i]]
//! @time O(n)
//! @space O(n)
vi mono_range(const vi& le) {
  vi ri(sz(le), sz(le));
  rep(i, 0, sz(le)) for (int j = i - 1; j != le[i];
                         j = le[j]) ri[j] = i;
  return ri;
}
