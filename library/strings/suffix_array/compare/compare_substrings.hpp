#pragma once
#include "compare_suffixes.hpp"
//! @code
//!   int cmp = s.cmp_substrs(le1,ri1,le2,ri2);
//! @endcode
//! requires le1,le2 < n
//! if cmp<0 then s[le1,ri1) < s[le2,ri2)
//! if cmp=0 then s[le1,ri1) = s[le2,ri2)
//! if cmp>0 then s[le1,ri1) > s[le2,ri2)
//! @time O(1)
//! @space O(1)
int cmp_substrs(int le1, int ri1, int le2, int ri2) {
  int len1 = ri1 - le1, len2 = ri2 - le2;
  return len_lcp(le1, le2) >= min(len1, len2)
    ? len1 - len2
    : cmp_sufs(le1, le2);
}
