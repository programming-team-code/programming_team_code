/** @file */
#pragma once
/**
 * @param t query string
 * @returns range [le, ri) such that:
 *     - for all i in [le, ri): t == s.substr(sa[i], sz(t))
 *     - `ri - le` is the # of matches of t in s.
 * @time O(|t| + log(|s|))
 * @space O(1)
 */
pii find_str_fast(const T& t) {
  int le = lower_bound(all(sa), 0, [&](int i, int) -> bool { return lexicographical_compare(i + all(s), all(t)); }) - begin(sa);
  if (le == n || mismatch(all(t), sa[le] + all(s)).first != end(t)) return {le, le};
  int ri = lower_bound(le + all(sa), 0, [&](int i, int) -> bool { return len_lcp(i, sa[le]) >= sz(t); }) - begin(sa);
  return {le, ri};
}
