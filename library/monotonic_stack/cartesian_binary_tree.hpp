#pragma once
#include "monotonic_stack.hpp"
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
vi cart_binary_tree(const vi& le) {
  vi p(le);
  rep(i, 0, sz(p)) for (int j = i - 1; j != le[i];
                        j = le[j]) if (le[j] == le[i])
    p[j] = i;
  return p;
}
