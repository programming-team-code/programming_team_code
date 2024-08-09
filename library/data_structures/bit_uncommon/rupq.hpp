/** @file */
#pragma once
#include "../bit.hpp"
/**
 * range update, point query
 */
template <class T> struct bit_rupq {
  int n;
  BIT<T> bit = {0};
  /**
   * @param a_n size
   * @time O(n)
   * @space O(n)
   */
  bit_rupq(int a_n) : n(a_n), bit(n) {}
  /**
   * @param a initial array
   * @time O(n)
   * @space O(n)
   */
  bit_rupq(vector<T> a) : n(sz(a)) {
    adjacent_difference(all(a), begin(a));
    bit = {a};
  }
  /**
   * does a[le] += d, a[le + 1] += d, .., a[ri - 1] += d
   *
   * @param le,ri defines range [le, ri)
   * @param d delta to add to all indexes in range
   * @time O(log n)
   * @space O(1)
   */
  void update(int le, int ri, T d) {
    if (le < n) bit.update(le, d);
    if (ri < n) bit.update(ri, -d);
  }
  /**
   * @param i index
   * @returns a[i]
   * @time O(log n)
   * @space O(1)
   */
  T get_index(int i) {
    return bit.query(i + 1);
  }
};
