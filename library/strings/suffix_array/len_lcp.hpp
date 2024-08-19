/** @file */
#pragma once
#include "suffix_array.hpp"
#include "../../data_structures/rmq.hpp"
template <class T> struct sa_query {
  T s;
  int n;
  vi sa, sa_inv, lcp;
  RMQ<int, function<int(int, int)>> rmq;
  sa_query(const T& a_s, const array<vi, 3>& x) : s(a_s), n(sz(s)), sa(x[0]), sa_inv(x[1]), lcp(x[2]),
    rmq(lcp, [](int x, int y) { return min(x, y); }) {}
  sa_query(const T& a_s, int max_val) : sa_query(a_s, get_sa(a_s, max_val)) {}
  /**
   * @param i1,i2 defines suffixes [i1, n), [i2, n)
   *      - if one of the suffixes is the entire string (i1 == 0 || i2 == 0) then
   *        it's the same as z algorithm
   * @returns max integer k such that s.substr(i1, k) == s.substr(i2, k)
   * @time O(1)
   * @space O(1)
   */
  int len_lcp(int i1, int i2) {
    if (i1 == i2) return n - i1;
    auto [le, ri] = minmax(sa_inv[i1], sa_inv[i2]);
    return rmq.query(le, ri);
  }
};
