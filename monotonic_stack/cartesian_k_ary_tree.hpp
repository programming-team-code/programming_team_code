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
//!   when cmp is less():
//!   a = {2, 1, 3, 1, 1, 0, 1, 2, 2, 0, 2}
//!       (---------------------------x---)
//!       (------------x)   (x------) | (x)
//!       (x)   (x)    |     | (---x) |  |
//!        |     |     |     |     |  |  |
//! index: 0  1  2  3  4  5  6  7  8  9  10
//!
//! nodes are the right-most min/max of their subarray:
//! p[0] = p[2] = 4
//! p[8] = 6
//! p[4] = p[6] = p[10] = 9
//! p[9] = -1 (root)
//!
//! indexes 1, 3, 5, 7 are not nodes; here p maps i to
//! right-most min/max in their subarray: p[1] = p[3] = 4
//! p[7] = 8
//! p[5] = 9
//!
//! @code
//!     auto le = mono_st(a, less()), p =
//!     cart_k_ary_tree(a, le); // min cart tree auto le =
//!     mono_st(a, greater()), p = cart_k_ary_tree(a, le);
//!     // max cart tree bool is_node = (p[i] < i || a[i]
//!     != a[p[i]]);
//! @endcode
//!
//! @param a,l array and its left-monotonic stack
//! @returns parent array
//! @time O(n)
//! @space a O(n) vector is allocated and returned
vector<int> cart_k_ary_tree(const auto& a,
  const vector<int>& l) {
  vector<int> p(l);
  for (int i = ssize(a) - 1; i >= 0; i--)
    for (int j = i - 1; j != l[i]; j = l[j])
      if (l[j] == l[i] || a[i] == a[l[j]])
        p[j] = (p[i] < i || a[i] != a[p[i]] ? i : p[i]);
  return p;
}
