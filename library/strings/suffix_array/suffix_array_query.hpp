#pragma once
#include "suffix_array.hpp"
#include "../../data_structures/rmq.hpp"
#include "find/match.hpp"
//! @code
//!   auto [sa1, sa_inv1, lcp1] = get_sa(s, 256);
//!   sa_query saq(s, sa1, sa_inv1, lcp1);
//! @endcode
template<class T> struct sa_query {
  int n;
  T s;
  vi sa, sa_inv, lcp;
  RMQ<int, function<int(int, int)>> rmq;
  sa_query(const T& s, const vi& sa, const vi& sa_inv,
    const vi& lcp):
    n(sz(s)), s(s), sa(sa), sa_inv(sa_inv), lcp(lcp),
    rmq(lcp, [](int x, int y) { return min(x, y); }) {}
  //! returns max integer k such that
  //!   s.substr(i1, k) == s.substr(i2, k)
  //! @time O(1)
  //! @space O(1)
  int len_lcp(int i1, int i2) {
    if (i1 == i2) return n - i1;
    auto [l, r] = minmax(sa_inv[i1], sa_inv[i2]);
    return rmq.query(l, r);
  }
#include "compare/compare_suffixes.hpp"
#include "compare/compare_substrings.hpp"
#include "find/find_string_bs.hpp"
#include "find/find_string_bs_fast.hpp"
#include "find/find_substring.hpp"
#include "find/find_substrings_concatenated.hpp"
};
