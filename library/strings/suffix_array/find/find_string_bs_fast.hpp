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
  int le = lower_bound(all(sa), 0, [&](int i, int) -> bool {
             int curr_len_lcp = prev_idx == -1 ? 0 : len_lcp(i, prev_idx);
             if (cnt_matched_prev == sz(t)) return curr_len_lcp < sz(t);
             if (cnt_matched_prev == curr_len_lcp) {
               auto [it_s, it_t] = mismatch(i + cnt_matched_prev + all(s), cnt_matched_prev + all(t));
               prev_idx = i, cnt_matched_prev = it_t - begin(t);
               return it_t != end(t) && (it_s == end(s) || *it_s < *it_t);
             }
             bool cond = 0;
             if (prev_idx != -1) {
               cond = prev_idx + cnt_matched_prev == n || s[prev_idx + cnt_matched_prev] < t[cnt_matched_prev];
             }
             if (cnt_matched_prev < curr_len_lcp) {
               return cond;
             } else {
               return !cond;
             }
           }) -
           begin(sa);

  int le_naive = lower_bound(begin(sa), end(sa), 0, [&](int i, int) -> bool { return lexicographical_compare(i + begin(s), end(s), begin(t), end(t)); }) - begin(sa);
  assert(le_naive == le);

  if (le == n || mismatch(all(t), sa[le] + all(s)).first != end(t)) return {le, le};
  int ri = lower_bound(le + all(sa), 0, [&](int i, int) -> bool { return len_lcp(i, sa[le]) >= sz(t); }) - begin(sa);
  return {le, ri};
}

