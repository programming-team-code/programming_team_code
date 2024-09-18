#pragma once
//! @code{.cpp}
//!     vector<ll> a;
//!     vi le = mono_st(a, less()); // greater(), less_equal(), greater_equal()
//! @endcode
//! @param a array
//! @param cmp transitive compare operator
//! @returns vector le where le[i] = max index such that: le[i] < i and
//!          cmp(a[le[i]], a[i]). If no index exists, le[i] = -1
//! @time O(n)
//! @space a O(n) vector is allocated and returned
template<class T, class F>
vi mono_st(const vector<T>& a, F cmp) {
  vi le(sz(a));
  rep(i, 0, sz(a)) for (le[i] = i - 1;
                        le[i] >= 0 && !cmp(a[le[i]], a[i]);)
    le[i] = le[le[i]];
  return le;
}
