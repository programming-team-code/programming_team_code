/** @file */
#pragma once
#include "../len_lcp.hpp"
/**
 * @param s_le,s_ri defines a substring [s_le, s_ri) of s
 * @returns a range [le, ri) such that:
 *     - for all i in [le, ri): s.substr(s_le, s_ri - s_le) == s.substr(sa[i], s_ri - s_le)
 *     - `ri - le` is the # of matches of s.substr(s_le, s_ri - s_le) in s.
 * @time O(log(|s|))
 * @space O(1)
 */
pii find_substr(int s_le, int s_ri) {
  auto cmp = [&](int i, bool flip) -> bool {
    return flip ^ (len_lcp(i, s_le) < s_ri - s_le);
  };
  int le = lower_bound(begin(sa), begin(sa) + sa_inv[s_le], 0, cmp) - begin(sa);
  int ri = lower_bound(sa_inv[s_le] + 1 + all(sa), 1, cmp) - begin(sa);
  return {le, ri};
}
