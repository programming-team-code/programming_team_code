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
  // TODO: combine both cases into one
  // TODO: make it not depend on find_substr
  if (empty(t)) return {0, n};  // TODO: remove this special case
  int le = -1, ri = -1;
  int cnt_matched_le = 0;
  int cnt_matched_ri = 0;
  auto _ = lower_bound(all(sa), 0, [&](int i, int) -> bool {
    if (cnt_matched_le >= cnt_matched_ri) {
      int curr_len_lcp = le == -1 ? 0 : len_lcp(i, le);
      if (cnt_matched_le < curr_len_lcp) {
        le = i;
        return 1;
      } else if (cnt_matched_le > curr_len_lcp) {
        ri = i;
        return 0;
      } else {
        assert(equal(begin(t), begin(t) + cnt_matched_le, i + begin(s)));
        int cnt_matched_mid = mismatch(cnt_matched_le + all(t), i + cnt_matched_le + all(s)).first - begin(t);
        if (cnt_matched_mid == sz(t)) {
          ri = i, cnt_matched_ri = cnt_matched_mid;
          return 0;
        }
        if (i + cnt_matched_mid == n || s[i + cnt_matched_mid] < t[cnt_matched_mid]) {
          le = i, cnt_matched_le = cnt_matched_mid;
          return 1;
        } else {
          ri = i, cnt_matched_ri = cnt_matched_mid;
          return 0;
        }
      }
    } else {
      int curr_len_lcp = len_lcp(ri, i);
      if (cnt_matched_ri < curr_len_lcp) {
        ri = i;
        return 0;
      } else if (cnt_matched_ri > curr_len_lcp) {
        le = i;
        return 1;
      } else {
        assert(equal(begin(t), begin(t) + cnt_matched_ri, i + begin(s)));
        int cnt_matched_mid = mismatch(cnt_matched_ri + all(t), i + cnt_matched_ri + all(s)).first - begin(t);
        if (cnt_matched_mid == sz(t)) {
          ri = i, cnt_matched_ri = cnt_matched_mid;
          return 0;
        }
        if (i + cnt_matched_mid < n && s[i + cnt_matched_mid] > t[cnt_matched_mid]) {
          ri = i, cnt_matched_ri = cnt_matched_mid;
          return 0;
        } else {
          le = i, cnt_matched_le = cnt_matched_mid;
          return 1;
        }
      }
    }
  });

  /*
  if (cnt_matched_le == sz(t)) {
    int le_naive = lower_bound(begin(sa), end(sa), 0, [&](int i, int) -> bool { return lexicographical_compare(i + begin(s), end(s), begin(t), end(t)); }) - begin(sa);
    assert(le_naive == le);
  }
  */

  if (cnt_matched_le == sz(t)) return find_substr(le, le + sz(t));
  if (cnt_matched_ri == sz(t)) return find_substr(ri, ri + sz(t));
  return {0, 0};
}

