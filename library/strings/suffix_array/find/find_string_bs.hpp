#pragma once
//! https://github.com/yosupo06/Algorithm/blob/master/src/string/suffixarray.hpp
//! returns range [le,ri) such that:
//!   - for all i in [le,ri): t==s.substr(sa[i],sz(t))
//!   - `ri-le` is the # of matches of t in s.
//! @time O(|t| * log(|s|))
//! @space O(1)
pii find_str(const T& t) {
  int le =
    lower_bound(all(sa), 0,
      [&](int i, int) -> bool {
        return lexicographical_compare(i + all(s), all(t));
      }) -
    begin(sa);
  int ri = lower_bound(le + all(sa), 0,
             [&](int i, int) -> bool {
               return mismatch(all(t), i + all(s)).first ==
                 end(t);
             }) -
    begin(sa);
  return {le, ri};
}
