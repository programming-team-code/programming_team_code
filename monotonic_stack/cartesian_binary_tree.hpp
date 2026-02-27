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
//!   // right-most min is root
//!   auto le = mono_st(a, less());
//!   auto p = cart_binary_tree(le);
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
vector<int> cart_binary_tree(const vector<int>& l) {
  vector<int> p(l);
  for (int i = 0; i < ssize(p); i++)
    for (int j = i - 1; j != l[i]; j = l[j])
      if (l[j] == l[i]) p[j] = i;
  return p;
}
