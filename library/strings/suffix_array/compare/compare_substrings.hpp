/** @file */
#pragma once
#include "compare_suffixes.hpp"
/**
 * @param le1,ri1 first substring [le1, ri1)
 * @param le2,ri2 second substring [le2, ri2)
 *     - doesn't work when le1,le2 == n
 * @returns a number `cmp` where:
 *     - cmp < 0 iff s.substr(le1, ri1 - le1) < s.substr(le2, ri2 - le2)
 *     - cmp = 0 iff s.substr(le1, ri1 - le1) = s.substr(le2, ri2 - le2)
 *     - cmp > 0 iff s.substr(le1, ri1 - le1) > s.substr(le2, ri2 - le2)
 * @time O(1)
 * @space O(1)
 */
int cmp_substrs(int le1, int ri1, int le2, int ri2) {
  int len1 = ri1 - le1, len2 = ri2 - le2;
  return len_lcp(le1, le2) >= min(len1, len2) ? len1 - len2 : cmp_sufs(le1, le2);
}
