//! @code
//!   auto mono_le1 = mono_st(a, less());
//!   // less_equal(), greater(), greater_equal()
//! @endcode
//! when cmp == less():
//!   a[mono_le1[i]] < a[i]
//! @time O(n)
//! @space O(n)
template<class T, class F>
vector<int> mono_st(const vector<T>& a, F cmp) {
  vector<int> le((int)size(a));
  for (int i = 0; i < ((int)size(a)); i++)
    for (le[i] = i - 1;
         le[i] >= 0 && !cmp(a[le[i]], a[i]);)
      le[i] = le[le[i]];
  return le;
}
//! @code
//!   auto mono_le2 = mono_st(a, less());
//!   auto mono_ri2 = mono_range(mono_le2);
//!   // less_equal(), greater(), greater_equal()
//! @endcode
//! when cmp == less():
//!   a[mono_le2[i]] < a[i] >= a[mono_ri2[i]]
//! @time O(n)
//! @space O(n)
vector<int> mono_range(const vector<int>& le) {
  vector<int> ri((int)size(le), (int)size(le));
  for (int i = 0; i < ((int)size(le)); i++)
    for (int j = i - 1; j != le[i]; j = le[j]) ri[j] = i;
  return ri;
}
//! returns largest integer x such that there exists a
//! subarray a[le,ri) with: (ri-le) * min(a[le,ri)) == x
//! @time O(n)
//! @space O(n)
int64_t max_rect_histogram(const vector<int>& a) {
  vector<int> le(mono_st(a, less())), ri(mono_range(le));
  int64_t max_area = 0;
  for (int i = 0; i < ((int)size(a)); i++)
    max_area =
      max(max_area, int64_t(a[i]) * (ri[i] - le[i] - 1));
  return max_area;
}
