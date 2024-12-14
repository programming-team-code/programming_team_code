#pragma once
//! @code
//!   string s;
//!   auto [sa, sa_inv, lcp] = get_sa(s, 256);
//!   sa_query saq(s, sa, sa_inv, lcp);
//!   auto [sa_le,sa_ri] = saq.find_substr(s_l,s_r);
//! @endcode
//! requires s_l < n
//! for all i in [sa_le,sa_ri): s.substr(s_l,s_r-s_l)
//!   == s.substr(sa[i],s_r-s_l)
//!   - `r-l` is the # of matches of
//!       s.substr(s_l, s_r - s_l) in s.
//! @time O(log(|s|))
//! @space O(1)
pii find_substr(int s_l, int s_r) {
  auto cmp = [&](int i, bool flip) -> bool {
    return flip ^ (len_lcp(i, s_l) < s_r - s_l);
  };
  int l = lower_bound(begin(sa), begin(sa) + sa_inv[s_l],
            0, cmp) -
    begin(sa);
  int r = lower_bound(sa_inv[s_l] + 1 + all(sa), 1, cmp) -
    begin(sa);
  return {l, r};
}
