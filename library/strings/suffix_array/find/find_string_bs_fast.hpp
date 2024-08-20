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
  int prev_idx = n;
  int cnt_matched_prev = 0;
  bool prev_cond = 0;
  int le = lower_bound(all(sa), 0, [&](int i, int) -> bool {
             int curr_len_lcp = prev_idx == n ? 0 : len_lcp(i, prev_idx);
             if (cnt_matched_prev == sz(t)) return curr_len_lcp < sz(t);
             if (cnt_matched_prev == curr_len_lcp) {
               auto [it_s, it_t] = mismatch(i + cnt_matched_prev + all(s), cnt_matched_prev + all(t));
               prev_idx = i, cnt_matched_prev = it_t - begin(t);
               return prev_cond = it_t != end(t) && (it_s == end(s) || *it_s < *it_t);
             }
             if (cnt_matched_prev < curr_len_lcp) {
               return prev_cond;
             } else {
               return !prev_cond;
             }
           }) -
           begin(sa);

  int le_naive = lower_bound(begin(sa), end(sa), 0, [&](int i, int) -> bool { return lexicographical_compare(i + begin(s), end(s), begin(t), end(t)); }) - begin(sa);
  assert(le_naive == le);

  if (cnt_matched_prev < sz(t)) return {le, le};
  int ri = lower_bound(le + all(sa), 0, [&](int i, int) -> bool { return len_lcp(i, sa[le]) >= sz(t); }) - begin(sa);
  return {le, ri};
}

