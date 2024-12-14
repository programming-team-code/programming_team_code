#pragma once
#include "compare_suffixes.hpp"
//! @code
//!   int cmp = saq.cmp_substrs(l1,r1,l2,r2);
//! @endcode
//! requires l1,l2 < n
//! if cmp1<0 then s[l1,r1) < s[l2,r2)
//! if cmp1=0 then s[l1,r1) = s[l2,r2)
//! if cmp1>0 then s[l1,r1) > s[l2,r2)
//! @time O(1)
//! @space O(1)
int cmp_substrs(int l1, int r1, int l2, int r2) {
  int len1 = r1 - l1, len2 = r2 - l2;
  return len_lcp(l1, l2) >= min(len1, len2)
    ? len1 - len2
    : cmp_sufs(l1, l2);
}
