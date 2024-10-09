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
//!   // right-most min is root
//!   auto mono_le3 = mono_st(a, less());
//!   auto p1 = cart_binary_tree(mono_le3);
//!
//!   // less_equal() -> left-most min is root
//!   // greater() -> right-most max is root
//!   // greater_equal() -> left-most max is root
//! @endcode
//! when cmp is less():
//! a = {2, 1, 3, 1, 1, 0, 2, 2, 1, 0, 2}
//!     (---------------------------x---)
//!     (---------------x---------)   (x)
//!     (------------x) | (------x)    |
//!     (---------x)    | (---x) |     |
//!     (---x---)       | (x) |  |     |
//!     (x) | (x)       |  |  |  |     |
//!      |  |  |        |  |  |  |     |
//!      0  1  2  3  4  5  6  7  8  9  10
//! @time O(n)
//! @space O(n)
vector<int> cart_binary_tree(const vector<int>& le) {
  vector<int> p(le);
  for (int i = 0; i < ((int)size(p)); i++)
    for (int j = i - 1; j != le[i]; j = le[j])
      if (le[j] == le[i]) p[j] = i;
  return p;
}
