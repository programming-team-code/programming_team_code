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
  vector<int> l(ssize(a));
  for (int i = 0; i < ssize(a); i++)
    for (l[i] = i - 1; l[i] >= 0 && !cmp(a[l[i]], a[i]);)
      l[i] = l[l[i]];
  return l;
}
