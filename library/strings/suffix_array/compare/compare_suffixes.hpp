#pragma once
//! @code
//!   auto [sa, sa_inv, lcp] = get_sa(s, 256);
//!   sa_query saq(s, sa, sa_inv, lcp);
//!   int cmp = saq.cmp_sufs(l1,l2);
//! @endcode
//! requires l1,l2 < n
//! if cmp2<0 then s[l1,n) < s[l2,n)
//! if cmp2=0 then s[l1,n) = s[l2,n)
//! if cmp2>0 then s[l1,n) > s[l2,n)
//! @time O(1)
//! @space O(1)
int cmp_sufs(int l1, int l2) {
  return sa_inv[l1] - sa_inv[l2];
}
