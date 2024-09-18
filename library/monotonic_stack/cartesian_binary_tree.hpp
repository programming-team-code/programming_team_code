#pragma once
#include "monotonic_stack.hpp"
//!   when cmp is less():
//!   a = {2, 1, 3, 1, 1, 0, 2, 2, 1, 0, 2}
//!       (---------------------------x---)
//!       (---------------x---------)   (x)
//!       (------------x) | (------x)    |
//!       (---------x)    | (---x) |     |
//!       (---x---)       | (x) |  |     |
//!       (x) | (x)       |  |  |  |     |
//!        |  |  |        |  |  |  |     |
//! index: 0  1  2  3  4  5  6  7  8  9  10
//!
//! @code{.cpp}
//!     auto le = mono_st(a, less()), p =
//!     cart_binary_tree(le); // right-most min is root auto
//!     le = mono_st(a, less_equal()), p =
//!     cart_binary_tree(le); // left-most min is root auto
//!     le = mono_st(a, greater()), p = cart_binary_tree(le);
//!     // right-most max is root auto le = mono_st(a,
//!     greater_equal()), p = cart_binary_tree(le); //
//!     left-most max is root
//! @endcode
//! @param le monotonic stack of array `a`
//! @returns parent array
//! @time O(n)
//! @space a O(n) vector is allocated and returned
vi cart_binary_tree(const vi& le) {
  vi p(le);
  rep(i, 0, sz(p)) for (int j = i - 1; j != le[i];
                        j = le[j]) if (le[j] == le[i]) p[j] =
    i;
  return p;
}
