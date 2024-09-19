#pragma once
//! @code
//!   int cmp = s.cmp_sufs(le1,le2);
//! @endcode
//! requires le1,le2 < n
//! if cmp<0 then s[le1,n) < s[le2,n)
//! if cmp=0 then s[le1,n) = s[le2,n)
//! if cmp>0 then s[le1,n) > s[le2,n)
//! @time O(1)
//! @space O(1)
int cmp_sufs(int le1, int le2) {
  return sa_inv[le1] - sa_inv[le2];
}
