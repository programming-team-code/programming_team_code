/** @file */
#pragma once
#include "../../data_structures/rmq.hpp"
#include "manacher.hpp"
/**
 * queries for longest palindromic substring of a given substring
 */
template <class T> struct longest_pal_query {
  vi man, idx;
  RMQ<int, function<int(int, int)>> rmq = {{}, []{}};
  /**
   * @param s string/vector
   * @time O(n log n)
   * @space O(n log n) for rmq, everything else is O(n)
   */
  longest_pal_query(const T& s) : man(manacher(s)), idx(sz(s)) {
    iota(all(idx), 1);
    vi init(sz(man));
    iota(all(init), 0);
    rmq = {init, [&](int i1, int i2) { return len(i1) < len(i2) ? i2 : i1; }};
  }
  /**
   * @param i center
   * @returns length of longest palindrome around center
   * @time O(1)
   * @space O(1)
   */
  int len(int i) { return i - 2 * man[i] + 1; }
  /**
   * approach: binary search: is there some palindromic substring with length >= mid ?
   * note for a substring [le, ri) of s, the "relevant" centers are subarray [2 * le, 2 * ri - 1) of `man`
   *
   * when center i (in "relevant" range) is even (so represents an odd-length palindrome):
   *     - i / 2 is index of middle of palindrome
   *     - le <= i / 2 < ri
   * when center i (in "relevant" range) is odd (so represents an even-length palindrome):
   *     - (i - 1) / 2, (i + 1) / 2 are indexes of middles of palindrome
   *     - le <= (i - 1) / 2 < (i + 1) / 2 < ri
   *
   * @param le,ri defines substring [le, ri) of s
   * @returns {start index, length} of longest palindromic substring of s.substr(le, ri - le)
   *     if there are multiple longest answers, this returns an arbitrary start index
   * @time O(log n)
   * @space O(1)
   */
  pii longest_pal(int le, int ri) {
    assert(0 <= le && le < ri && ri <= sz(idx));
    int pal_len = lower_bound(begin(idx), begin(idx) + (ri - le), 0,
                              [&](int mid, int) { return len(rmq.query(2 * le + mid - 1, 2 * ri - mid)) >= mid; }) -
                  begin(idx);
    int best_center = rmq.query(2 * le + pal_len - 1, 2 * ri - pal_len);
    return {(best_center + 1 - pal_len) / 2, pal_len};
  }
};
