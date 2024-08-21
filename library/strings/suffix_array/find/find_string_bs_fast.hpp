/** @file */
#pragma once
#include "match.hpp"
/**
 * @see https://stackoverflow.com/a/11374737
 * @param t query string
 * @returns see match
 * @time O(|t| + log(|s|))
 * @space O(1)
 */
match find_str_fast(const T& t) {
  int s_le = n, s_len = 0;
  bool s_less = 0;
  int sa_le = lower_bound(all(sa), 0, [&](int i, int) -> bool {
    if (int lcp_len = s_le == n ? 0 : len_lcp(i, s_le); s_len != lcp_len)
      return s_less ^ (s_len > lcp_len);
    auto [it_s, it_t] = mismatch(i + s_len + all(s), s_len + all(t));
    s_le = i, s_len = it_t - begin(t);
    return s_less = lexicographical_compare(it_s, end(s), it_t, end(t));
  }) - begin(sa);
  if (s_len < sz(t)) return {sa_le, sa_le, s_le, s_le + s_len};
  int sa_ri = lower_bound(sa_le + all(sa), 0, [&](int i, int) -> bool { return len_lcp(i, s_le) >= sz(t); }) - begin(sa);
  return {sa_le, sa_ri, s_le, s_le + s_len};
}
