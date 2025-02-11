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
//! returns largest integer x such that there exists a
//! subarray a[l,r) with: (r-l) * min(a[l,r)) == x
//! @time O(n)
//! @space O(n)
int64_t max_rect_histogram(const vector<int>& a) {
  vector<int> l(mono_st(a, less())), r(mono_range(l));
  int64_t max_area = 0;
  for (int i = 0; i < ssize(a); i++)
    max_area =
      max(max_area, int64_t(a[i]) * (r[i] - l[i] - 1));
  return max_area;
}
