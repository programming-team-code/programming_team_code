#pragma once
#include "monotonic_stack.hpp"
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
//! @code{.cpp}
//!     auto le = mono_st(a, less()), p = cart_k_ary_tree(a,
//!     le); // min cart tree auto le = mono_st(a,
//!     greater()), p = cart_k_ary_tree(a, le); // max cart
//!     tree bool is_node = (p[i] < i || a[i] != a[p[i]]);
//! @endcode
//!
//! @param a,le array and its left-monotonic stack
//! @returns parent array
//! @time O(n)
//! @space a O(n) vector is allocated and returned
template<class T>
vi cart_k_ary_tree(const vector<T>& a, const vi& le) {
  vi p(le);
  for (int i = sz(a) - 1; i >= 0; i--)
    for (int j = i - 1; j != le[i]; j = le[j])
      if (le[j] == le[i] || a[i] == a[le[j]])
        p[j] = (p[i] < i || a[i] != a[p[i]] ? i : p[i]);
  return p;
}
