RMQ<int, function<int(int, int)>> rmq;
/**
 * @param i1,i2 defines substrings [i1, n), [i2, n)
 *      - passing i1,i2 = n is okay
 *      - if one of the suffixes is the entire string (i1 == 0 || i2 == 0) then
 *        it's the same as z algorithm
 * @returns max integer k such that s.substr(i1, k) == s.substr(i2, k)
 * @time O(1)
 * @space O(1)
 */
inline int len_lcp(int i1, int i2) {
  if (i1 > i2) swap(i1, i2);
  assert(0 <= i1 && i2 <= n);
  if (i1 == i2 || i2 == n) return n - i2;
  if (empty(rmq.dp)) rmq = {lcp, [](int x, int y) { return min(x, y); }};
  auto [le, ri] = minmax(sa_inv[i1], sa_inv[i2]);
  return rmq.query(le, ri);
}
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
 * @param substrs this defines query string t as:
 *     s.substr(substrs[0][0], substrs[0][1] - substrs[0][0]) +
 *     s.substr(substrs[1][0], substrs[1][1] - substrs[1][0]) +
 *     ...
 *     s.substr(substrs.back()[0], substrs.back()[1] - substrs.back()[0])
 * @returns see match
 * @time O(sz(substrs) * log(|s|))
 * @space O(1)
 */
inline match find_substrs_concated(const vector<pair<int, int>>& substrs) {
  using dt = array<int, 3>;
  int sa_le = 0, sa_ri = n, s_le = 0, s_ri = 0, sum_len = 0;
  auto cmp = [&](int i, const dt& x) -> bool {
    int j = i + sum_len, lcp_len = min(len_lcp(j, x[0]), x[1]);
    if (lcp_len + sum_len > s_ri - s_le) s_le = i, s_ri = j + lcp_len;
    if (lcp_len < min(n - j, x[1])) return sa_inv[j] - sa_inv[x[0]] < x[2];
    return x[2] ^ (n - j < x[1]);
  };
  for (auto [le, ri] : substrs) {
    assert(0 <= le && le <= ri && ri <= n);
    sa_le = lower_bound(begin(sa) + sa_le, begin(sa) + sa_ri, dt{le, ri - le, 0}, cmp) - begin(sa);
    sa_ri = lower_bound(begin(sa) + sa_le, begin(sa) + sa_ri, dt{le, ri - le, 1}, cmp) - begin(sa);
    sum_len += ri - le;
  }
  return {sa_le, sa_ri, s_le, s_ri};
}
