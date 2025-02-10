#pragma once
//! @code
//!   vi le = mono_st(a, less());
//!   // less_equal(), greater(), greater_equal()
//! @endcode
//! when cmp == less():
//!   a[le[i]] < a[i]
//! @time O(n)
//! @space O(n)
vi mono_st(const auto& a, auto cmp) {
  vi l(sz(a));
  rep(i, 0, sz(a)) for (l[i] = i - 1;
    l[i] >= 0 && !cmp(a[l[i]], a[i]);) l[i] = l[l[i]];
  return l;
}
