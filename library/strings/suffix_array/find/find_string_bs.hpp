/** @file */
#pragma once
/**
 * @see https://github.com/yosupo06/Algorithm/blob /master/src/string/suffixarray.hpp
 * @param t query string
 * @returns range [le, ri) such that:
 *     - for all i in [le, ri): t == s.substr(sa[i], sz(t))
 *     - `ri - le` is the # of matches of t in s.
 * @time O(|t| * log(|s|))
 * @space O(1)
 */
inline array<int, 2> find_str(const T& t) {
  int le = lower_bound(begin(sa), end(sa), 0,
                       [&](int i, int) -> bool { return lexicographical_compare(begin(s) + i, end(s), begin(t), end(t)); }) -
           begin(sa);
  int ri = lower_bound(begin(sa) + le, end(sa), 0,
                       [&](int i, int) -> bool { return mismatch(begin(t), end(t), begin(s) + i, end(s)).first == end(t); }) -
           begin(sa);
  return {le, ri};
}
