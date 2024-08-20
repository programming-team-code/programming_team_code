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
  int prev_idx = -1;
  int cnt_matched_prev = 0;
  bool cond = 0;
  int le = lower_bound(all(sa), 0, [&](int i, int) -> bool {
             int curr_len_lcp = prev_idx == -1 ? 0 : len_lcp(i, prev_idx);
             if (cnt_matched_prev == sz(t)) {
               bool naive = lexicographical_compare(i + begin(s), end(s), begin(t), end(t));
               assert(naive == (curr_len_lcp < sz(t)));
               return naive;
             }
             if (cnt_matched_prev < curr_len_lcp) {
               return cond;
             } else if (cnt_matched_prev > curr_len_lcp) {
               return !cond;
             } else {
               int cnt_matched_mid = mismatch(cnt_matched_prev + all(t), i + cnt_matched_prev + all(s)).first - begin(t);
               if (cnt_matched_mid == sz(t)) {
                 prev_idx = i, cnt_matched_prev = cnt_matched_mid;
                 return 0;
               }
               prev_idx = i, cnt_matched_prev = cnt_matched_mid;
               return cond = i + cnt_matched_mid == n || s[i + cnt_matched_mid] < t[cnt_matched_mid];
             }
           }) -
           begin(sa);

  int le_naive = lower_bound(begin(sa), end(sa), 0, [&](int i, int) -> bool { return lexicographical_compare(i + begin(s), end(s), begin(t), end(t)); }) - begin(sa);
  assert(le_naive == le);

  if (le == n || mismatch(all(t), sa[le] + all(s)).first != end(t)) return {le, le};
  int ri = lower_bound(le + all(sa), 0, [&](int i, int) -> bool { return len_lcp(i, sa[le]) >= sz(t); }) - begin(sa);
  return {le, ri};
}

