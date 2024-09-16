//! @file
#pragma once
//! subarray of `sa` of matches, and example of
//! longest matching prefix of t in s
struct match {
  //! t is some string defined by the query
  //!
  //! [sa_le, sa_ri) defines subarray of suffix
  //! array such that:
  //! - for all i in [sa_le, sa_ri): t ==
  //! s.substr(sa[i], sz(t))
  //! - `sa_ri - sa_le` is the # of matches of t in
  //! s.
  //!
  //! [s_le, s_ri) defines a substring of s such
  //! that:
  //! - s.substr(s_le, s_ri - s_le) == t.substr(0,
  //! s_ri - s_le)
  //! - (s_ri - s_le) is maximized, if there are
  //! multiple answers, s_le is arbitrary
  //!
  //! - note if sa_le < sa_ri, i.e. at least one
  //! match, then s_ri - s_le == sz(t)
  //! - note if sa_le == sa_ri, i.e. no matches,
  //! then s_ri - s_le < sz(t)
  //! @{
  int sa_le, sa_ri, s_le, s_ri;
  //! @}
};
