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
  int idx = n;
  int cnt = 0;
  bool s_less = 0;
  int le = lower_bound(all(sa), 0, [&](int i, int) -> bool {
             int curr_len_lcp = idx == n ? 0 : len_lcp(i, idx);
             if (cnt == sz(t)) return curr_len_lcp < sz(t);
             if (cnt == curr_len_lcp) {
               auto [it_s, it_t] = mismatch(i + cnt + all(s), cnt + all(t));
               idx = i, cnt = it_t - begin(t);
               return s_less = it_t != end(t) && (it_s == end(s) || *it_s < *it_t);
             }
             if (cnt < curr_len_lcp) {
               return s_less;
             } else {
               return !s_less;
             }
           }) -
           begin(sa);

  int le_naive = lower_bound(begin(sa), end(sa), 0, [&](int i, int) -> bool { return lexicographical_compare(i + begin(s), end(s), begin(t), end(t)); }) - begin(sa);
  assert(le_naive == le);

  if (cnt < sz(t)) return {le, le};
  int ri = lower_bound(le + all(sa), 0, [&](int i, int) -> bool { return len_lcp(i, sa[le]) >= sz(t); }) - begin(sa);
  return {le, ri};
}

