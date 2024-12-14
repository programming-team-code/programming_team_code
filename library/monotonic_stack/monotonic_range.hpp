#pragma once
#include "monotonic_stack.hpp"
//! @code
//!   vi le = mono_st(a, less()), ri = mono_range(le);
//!   // less_equal(), greater(), greater_equal()
//! @endcode
//! when cmp == less():
//!   a[le[i]] < a[i] >= a[ri[i]]
//! @time O(n)
//! @space O(n)
vi mono_range(const vi& l) {
  vi r(sz(l), sz(l));
  rep(i, 0, sz(l)) for (int j = i - 1; j != l[i]; j = l[j])
    r[j] = i;
  return r;
}
