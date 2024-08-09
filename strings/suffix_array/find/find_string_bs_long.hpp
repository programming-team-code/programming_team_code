/**
 * subarray of `sa` of matches, and example of longest matching prefix of t in s
 */
struct match {
  /**
   * t is some string defined by the query
   *
   * [sa_le, sa_ri) defines subarray of suffix array such that:
   * - for all i in [sa_le, sa_ri): t == s.substr(sa[i], sz(t))
   * - `sa_ri - sa_le` is the # of matches of t in s.
   *
   * [s_le, s_ri) defines a substring of s such that:
   * - s.substr(s_le, s_ri - s_le) == t.substr(0, s_ri - s_le)
   * - (s_ri - s_le) is maximized, if there are multiple answers, s_le is arbitrary
   *
   * - note if sa_le < sa_ri, i.e. at least one match, then s_ri - s_le == sz(t)
   * - note if sa_le == sa_ri, i.e. no matches, then s_ri - s_le < sz(t)
   * @{
   */
  int sa_le, sa_ri, s_le, s_ri;
  /** @} */
};
/**
 * @param t query string
 * @returns see match
 * @time O(|t| * log(|s|))
 * @space O(1)
 */
match find_str_long(const T& t) {
  int s_le = 0, s_ri = 0;
  auto cmp = [&](int i, int cmp_num) -> bool {
    auto [it_t, it_s] = mismatch(begin(t), end(t), i + begin(s), end(s));
    if (it_s - begin(s) - i > s_ri - s_le) s_le = i, s_ri = it_s - begin(s);
    if (it_s != end(s) && it_t != end(t)) return (*it_s) - (*it_t) < cmp_num;
    return cmp_num ^ ((int)size(s) - i < (int)size(t));
  };
  int sa_le = lower_bound(begin(sa), end(sa), 0, cmp) - begin(sa);
  int sa_ri = lower_bound(sa_le + begin(sa), end(sa), 1, cmp) - begin(sa);
  return {sa_le, sa_ri, s_le, s_ri};
}
