#pragma once
//! @param v node
//! @returns range [l, r) such that the following (r -
//! l) substrings are equal:
//!     - for all i in [l, r): s.substr(sa[i],
//!     lcp_len(v))
//! @time O(1)
//! @space O(1)
pii sa_range(int v) {
  if (v < sf_a.n - 1) return {l[v] + 1, r[v] + 1};
  return {v - sf_a.n + 1, v - sf_a.n + 2};
}
