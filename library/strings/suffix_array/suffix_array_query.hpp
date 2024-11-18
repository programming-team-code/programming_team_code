#pragma once
#include "suffix_array.hpp"
#include "../../data_structures/rmq.hpp"
#include "find/match.hpp"
//! @code
//!   auto [sa, sa_inv, lcp] = get_sa(s, 256);
//!   sa_query saq(s, sa, sa_inv, lcp);
//! @endcode
template<class T> struct sa_query {
  T s;
  int n;
  vi sa, sa_inv, lcp;
  RMQ<int, function<int(int, int)>> rmq;
  sa_query(const T& a_s, const vi& a_sa, const vi& a_inv,
    const vi& a_lcp):
    s(a_s), n(sz(s)), sa(a_sa), sa_inv(a_inv), lcp(a_lcp),
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
