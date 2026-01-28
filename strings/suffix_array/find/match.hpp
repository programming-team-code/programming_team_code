//! for all i in [sa_le,sa_ri):
//!   - t==s.substr(sa[i],sz(t))
//!   - `sa_ri-sa_le` is the # of matches of t in s.
//!
//! if sa_le==sa_ri then:
//!   s[s_l,s_r) is longest substring such that:
//!   s[s_l,s_r) == t[0,s_r-s_l)
struct match {
  int sa_le, sa_ri, s_l, s_r;
};
