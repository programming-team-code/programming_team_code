//! @file
#pragma once
/**
 * @param le1,le2 defines suffixes [le1, n), [le2, n)
 *     - doesn't work when le1,le2 == n
 * @returns a number `cmp` where:
 *     - cmp < 0 iff s.substr(le1) < s.substr(le2)
 *     - cmp = 0 iff s.substr(le1) = s.substr(le2)
 *     - cmp > 0 iff s.substr(le1) > s.substr(le2)
 * @time O(1)
 * @space O(1)
 */
int cmp_sufs(int le1, int le2) {
  return sa_inv[le1] - sa_inv[le2];
}
