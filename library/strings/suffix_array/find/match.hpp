#pragma once
//! for all i in [sa_le,sa_ri):
//!   - t==s.substr(sa[i],sz(t))
//!   - `sa_ri-sa_le` is the # of matches of t in s.
//!
//! if sa_le==sa_ri then:
//!   s[s_le,s_ri) is longest substring such that:
//!   s[s_le,s_ri) == t[0,s_ri-s_le)
struct match {
  int sa_le, sa_ri, s_le, s_ri;
};
