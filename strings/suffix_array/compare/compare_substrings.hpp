//! @code
//!   string s;
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
//! @code
//!   string s;
//!   auto [sa, sa_inv, lcp] = get_sa(s, 256);
//!   sa_query saq(s, sa, sa_inv, lcp);
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
