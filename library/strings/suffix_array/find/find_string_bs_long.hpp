/** @file */
#pragma once
#include "match.hpp"
/**
 * @param t query string
 * @returns see match
 * @time O(|t| * log(|s|))
 * @space O(1)
 */
inline match find_str_long(const T& t) {
  int s_le = 0, s_ri = 0;
  auto cmp = [&](int i, int cmp_num) -> bool {
    auto [it_t, it_s] = mismatch(all(t), i + all(s));
    if (it_s - begin(s) - i > s_ri - s_le) s_le = i, s_ri = it_s - begin(s);
    if (it_s != end(s) && it_t != end(t)) return (*it_s) - (*it_t) < cmp_num;
    return cmp_num ^ (sz(s) - i < sz(t));
  };
  int sa_le = lower_bound(all(sa), 0, cmp) - begin(sa);
  int sa_ri = lower_bound(sa_le + all(sa), 1, cmp) - begin(sa);
  return {sa_le, sa_ri, s_le, s_ri};
}
