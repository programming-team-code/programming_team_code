#pragma once
#include "../../data_structures/rmq.hpp"
#include "manacher.hpp"
//! queries for longest palindromic substring of a given
//! substring
template<class T> struct longest_pal_query {
  vi man;
  RMQ<int, function<int(int, int)>> rmq = {{}, nullptr};
  //! @param s string/vector
  //! @time O(n log n)
  //! @space O(n log n) for rmq, everything else is O(n)
  longest_pal_query(const T& s): man(manacher(s)) {
    vi init(sz(man));
    iota(all(init), 0);
    rmq = {init, [&](int i1, int i2) {
             return len(i1) < len(i2) ? i2 : i1;
           }};
  }
  //! @param i center
  //! @returns length of longest palindrome around center
  //! @time O(1)
  //! @space O(1)
  int len(int i) { return i - 2 * man[i] + 1; }
  //! approach: binary search: is there some palindromic
  //! substring with length >= mid ? note for a substring
  //! [l, r) of s, the "relevant" centers are subarray [2
  //! * l, 2 * r - 1) of `man`
  //!
  //! when center i (in "relevant" range) is even (so
  //! represents an odd-length palindrome):
  //!     - i / 2 is index of middle of palindrome
  //!     - l <= i / 2 < r
  //! when center i (in "relevant" range) is odd (so
  //! represents an even-length palindrome):
  //!     - (i - 1) / 2, (i + 1) / 2 are indexes of middles
  //!     of palindrome
  //!     - l <= (i - 1) / 2 < (i + 1) / 2 < r
  //!
  //! @param l,r defines substring [l, r) of s
  //! @returns {start index, length} of longest palindromic
  //! substring of s.substr(l, r - l)
  //!     if there are multiple longest answers, this
  //!     returns an arbitrary start index
  //! @time O(log n)
  //! @space O(1)
  pii longest_pal(int l, int r) {
    assert(l < r);
    int pal_len = *ranges::partition_point(
      views::iota(0, r - l), [&](int x) {
        return len(rmq.query(2 * l + x, 2 * r - x - 1)) >
          x;
      });
    int best_center =
      rmq.query(2 * l + pal_len - 1, 2 * r - pal_len);
    return {(best_center + 1 - pal_len) / 2, pal_len};
  }
};
