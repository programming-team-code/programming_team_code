/** @file */
#pragma once
#include "sa_range.hpp"
#include "len_lcp_range.hpp"
#include "get_child.hpp"
/**
 * performs trie-style downwards tree walk
 * @param t needle
 * @returns range [le, ri) such that:
 *     - for all i in [le, ri): t == s.substr(sa[i], sz(t))
 *     - `ri - le` is the # of matches of t in s.
 * @time O(|t|)
 * @space O(1)
 */
pii find_str(const string& t) {
  int v = root;
  rep(i, 0, sz(t)) {
    if (i == len_lcp_range(v)) {
      v = get_child(v, t[i]);
      if (v == -1) return {0, 0};
    }
    int sa_le = sa_range(v).first;
    if (sf_a.s[sf_a.sa[sa_le] + i] != t[i]) return {0, 0};
  }
  return sa_range(v);
}
