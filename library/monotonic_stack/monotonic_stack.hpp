#pragma once
//! @code
//!   auto le = mono_st(a, less());
//!   // less_equal(), greater(), greater_equal()
//! @endcode
//! when cmp == less():
//!   a[le[i]] < a[i]
//! @time O(n)
//! @space O(n)
template<class T, class F>
vi mono_st(const vector<T>& a, F cmp) {
  vi le(sz(a));
  rep(i, 0, sz(a)) for (
    le[i] = i - 1; le[i] >= 0 && !cmp(a[le[i]], a[i]);)
    le[i] = le[le[i]];
  return le;
}
