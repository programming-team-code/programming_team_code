//! @file
#pragma once
//! @param v node
//! @returns range [le, ri) such that the following (ri - le) substrings are equal:
//!     - for all i in [le, ri): s.substr(sa[i], lcp_len(v))
//! @time O(1)
//! @space O(1)
pii sa_range(int v) {
  if (v < sf_a.n - 1) return {le[v] + 1, ri[v] + 1};
  return {v - sf_a.n + 1, v - sf_a.n + 2};
}
