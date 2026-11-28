//! @code
//!   vector<int> l = mono_st(a, less());
//!   // less_equal(), greater(), greater_equal()
//! @endcode
//! when cmp == less():
//!   a[l[i]] < a[i]
//! @time O(n)
//! @space O(n)
vector<int> mono_st(const auto& a, const auto& cmp) {
  vector<int> l(ssize(a));
  for (int i = 0; i < ssize(a); i++)
    for (l[i] = i - 1; l[i] >= 0 && !cmp(a[l[i]], a[i]);) l[i] = l[l[i]];
  return l;
}
//! @code
//!   vector<int> l = mono_st(a, less()),
//!     r = mono_range(l);
//!   // less_equal(), greater(), greater_equal()
//! @endcode
//! when cmp == less():
//!   a[l[i]] < a[i] >= a[r[i]]
//! @time O(n)
//! @space O(n)
vector<int> mono_range(const vector<int>& l) {
  vector<int> r(ssize(l), ssize(l));
  for (int i = 0; i < ssize(l); i++)
    for (int j = i - 1; j != l[i]; j = l[j]) r[j] = i;
  return r;
}
