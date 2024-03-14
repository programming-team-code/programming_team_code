/** @file */
#pragma once
/**
 * @param u node
 * @returns range [le, ri) such that the following (ri - le) substrings are equal:
 *     - for all i in [le, ri): s.substr(sa[i], lcp_len(u))
 * @time O(1)
 * @space O(1)
 */
inline array<int, 2> sa_range(int u) {
  if (u < sf_a.n - 1) return {le[u] + 1, ri[u] + 1};
  return {u - sf_a.n + 1, u - sf_a.n + 2};
}
