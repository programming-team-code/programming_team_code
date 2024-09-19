#pragma once
#include "suffix_array.hpp"
#include "../../data_structures/rmq.hpp"
#include "find/match.hpp"
template<class T> struct sa_query {
  T s;
  int n;
  vi sa, sa_inv, lcp;
  RMQ<int, function<int(int, int)>> rmq;
  sa_query(const T& a_s, const array<vi, 3>& d):
    s(a_s), n(sz(s)), sa(d[0]), sa_inv(d[1]), lcp(d[2]),
    rmq(lcp, [](int x, int y) { return min(x, y); }) {}
  sa_query(const T& a_s, int max_val):
    sa_query(a_s, get_sa(a_s, max_val)) {}
  //! returns max integer k such that
  //!   s.substr(i1, k) == s.substr(i2, k)
  //! @time O(1)
  //! @space O(1)
  int len_lcp(int i1, int i2) {
    if (i1 == i2) return n - i1;
    auto [le, ri] = minmax(sa_inv[i1], sa_inv[i2]);
    return rmq.query(le, ri);
  }
#include "compare/compare_suffixes.hpp"
#include "compare/compare_substrings.hpp"
#include "find/find_string_bs.hpp"
#include "find/find_string_bs_fast.hpp"
#include "find/find_substring.hpp"
#include "find/find_substrings_concatenated.hpp"
};
