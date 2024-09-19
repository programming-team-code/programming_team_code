#pragma once
#include "monotonic_stack.hpp"
//! @code
//!   auto le = mono_st(a, less());
//!   auto ri = mono_range(le);
//!   // less_equal(), greater(), greater_equal()
//! @endcode
//! when cmp == less():
//!   a[le[i]] < a[i] >= a[ri[i]]
//! @time O(n)
//! @space O(n)
vi mono_range(const vi& le) {
  vi ri(sz(le), sz(le));
  rep(i, 0, sz(le)) for (int j = i - 1; j != le[i];
                         j = le[j]) ri[j] = i;
  return ri;
}
