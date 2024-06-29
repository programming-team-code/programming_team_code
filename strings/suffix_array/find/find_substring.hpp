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
 * @param s_le,s_ri defines a substring [s_le, s_ri) of s
 * @returns a range [le, ri) such that:
 *     - for all i in [le, ri): s.substr(s_le, s_ri - s_le) == s.substr(sa[i], s_ri - s_le)
 *     - `ri - le` is the # of matches of s.substr(s_le, s_ri - s_le) in s.
 * @time O(log(|s|))
 * @space O(1)
 */
inline pair<int, int> find_substr(int s_le, int s_ri) {
  assert(0 <= s_le && s_le <= s_ri && s_ri <= n);
  if (s_le == n) return {0, n};
  auto cmp = [&](int i, bool flip) -> bool {
    return flip ^ (len_lcp(i, s_le) < s_ri - s_le);
  };
  int le = lower_bound(begin(sa), begin(sa) + sa_inv[s_le], 0, cmp) - begin(sa);
  int ri = lower_bound(sa_inv[s_le] + 1 + begin(sa), end(sa), 1, cmp) - begin(sa);
  return {le, ri};
}
