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
  int prev_idx = -1;
  int cnt_matched_prev = 0;
  bool cond = 1;
  int le_res = lower_bound(all(sa), 0, [&](int i, int) -> bool {
                 if (max(cnt_matched_prev, cnt_matched_prev) == sz(t)) return 0;
                 if (cond) {
                   int curr_len_lcp = prev_idx == -1 ? 0 : len_lcp(i, prev_idx);
                   if (cnt_matched_prev < curr_len_lcp) {
                     return cond;
                   } else if (cnt_matched_prev > curr_len_lcp) {
                     return !cond;
                   } else {
                     assert(equal(begin(t), begin(t) + cnt_matched_prev, i + begin(s)));
                     int cnt_matched_mid = mismatch(cnt_matched_prev + all(t), i + cnt_matched_prev + all(s)).first - begin(t);
                     if (cnt_matched_mid == sz(t)) {
                       return 0;
                     }
                     if (i + cnt_matched_mid == n || s[i + cnt_matched_mid] < t[cnt_matched_mid]) {
                       prev_idx = i, cnt_matched_prev = cnt_matched_mid;
                       return cond;
                     } else {
                       if (cnt_matched_mid > cnt_matched_prev) {
                         prev_idx = i, cnt_matched_prev = cnt_matched_mid;
                         cond = !cond;
                       }
                       return 0;
                     }
                   }
                 } else {
                   int curr_len_lcp = len_lcp(prev_idx, i);
                   if (cnt_matched_prev < curr_len_lcp) {
                     return cond;
                   } else if (cnt_matched_prev > curr_len_lcp) {
                     return !cond;
                   } else {
                     assert(equal(begin(t), begin(t) + cnt_matched_prev, i + begin(s)));
                     int cnt_matched_mid = mismatch(cnt_matched_prev + all(t), i + cnt_matched_prev + all(s)).first - begin(t);
                     if (cnt_matched_mid == sz(t)) {
                       return 0;
                     }
                     if (i + cnt_matched_mid < n && s[i + cnt_matched_mid] > t[cnt_matched_mid]) {
                       prev_idx = i, cnt_matched_prev = cnt_matched_mid;
                       return cond;
                     } else {
                       prev_idx = i, cnt_matched_prev = cnt_matched_mid;
                       cond = !cond;
                       return 1;
                     }
                   }
                 }
               }) -
               begin(sa);
  int le_naive = lower_bound(begin(sa), end(sa), 0, [&](int i, int) -> bool { return lexicographical_compare(i + begin(s), end(s), begin(t), end(t)); }) - begin(sa);
  assert(le_naive == le_res);

  if (le_res == n || mismatch(all(t), sa[le_res] + all(s)).first != end(t)) return {le_res, le_res};
  int ri = lower_bound(le_res + all(sa), 0, [&](int i, int) -> bool { return len_lcp(i, sa[le_res]) >= sz(t); }) - begin(sa);
  return {le_res, ri};
}

