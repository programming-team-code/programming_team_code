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
  int le = 0;
  int cnt_matched_le = mismatch(all(t), sa[0] + all(s)).first - begin(t);
  int cnt_matched_ri = mismatch(all(t), sa.back() + all(s)).first - begin(t);
  int ri = n - 1;
  while (le + 1 < ri) {
    int mid = (le + ri) / 2;
    if (cnt_matched_le >= cnt_matched_ri) {
      int curr_len_lcp = len_lcp(sa[le], sa[mid]);
      if (cnt_matched_le < curr_len_lcp) le = mid;
      else if (cnt_matched_le > curr_len_lcp) ri = mid;
      else {
        assert(equal(begin(t), begin(t) + cnt_matched_le, sa[mid] + begin(s)));
        int cnt_matched_mid = mismatch(cnt_matched_le + all(t), sa[mid] + cnt_matched_le + all(s)).first - begin(t);
        if (cnt_matched_mid == sz(t)) return find_substr(sa[mid], sa[mid] + sz(t));
        if (sa[mid] + cnt_matched_mid == n || s[sa[mid] + cnt_matched_mid] < t[cnt_matched_mid])
          le = mid, cnt_matched_le = cnt_matched_mid;
        else
          ri = mid, cnt_matched_ri = cnt_matched_mid;
      }
    } else {
      int curr_len_lcp = len_lcp(sa[ri], sa[mid]);
      if (cnt_matched_ri < curr_len_lcp) ri = mid;
      else if (cnt_matched_ri > curr_len_lcp) le = mid;
      else {
        assert(equal(begin(t), begin(t) + cnt_matched_ri, sa[mid] + begin(s)));
        int cnt_matched_mid = mismatch(cnt_matched_ri + all(t), sa[mid] + cnt_matched_ri + all(s)).first - begin(t);
        if (cnt_matched_mid == sz(t)) return find_substr(sa[mid], sa[mid] + sz(t));
        if (sa[mid] + cnt_matched_mid < n && s[sa[mid] + cnt_matched_mid] > t[cnt_matched_mid])
          ri = mid, cnt_matched_ri = cnt_matched_mid;
        else
          le = mid, cnt_matched_le = cnt_matched_mid;
      }
    }
  }
  if (cnt_matched_le == sz(t)) return find_substr(sa[le], sa[le] + sz(t));
  if (cnt_matched_ri == sz(t)) return find_substr(sa[ri], sa[ri] + sz(t));
  return {0, 0};
}
