//! @code
//!   vi le = mono_st(a, less());
//!   // less_equal(), greater(), greater_equal()
//! @endcode
//! when cmp == less():
//!   a[le[i]] < a[i]
//! @time O(n)
//! @space O(n)
vector<int> mono_st(const auto& a, const auto& cmp) {
  vector<int> l(ssize(a));
  for (int i = 0; i < ssize(a); i++)
    for (l[i] = i - 1; l[i] >= 0 && !cmp(a[l[i]], a[i]);)
      l[i] = l[l[i]];
  return l;
}
//! @code
//!   vi le = mono_st(a, less()), ri = mono_range(le);
//!   // less_equal(), greater(), greater_equal()
//! @endcode
//! when cmp == less():
//!   a[le[i]] < a[i] >= a[ri[i]]
//! @time O(n)
//! @space O(n)
vector<int> mono_range(const vector<int>& l) {
  vector<int> r(ssize(l), ssize(l));
  for (int i = 0; i < ssize(l); i++)
    for (int j = i - 1; j != l[i]; j = l[j]) r[j] = i;
  return r;
}
