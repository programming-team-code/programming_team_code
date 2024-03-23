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
 * @param le1,ri1 first substring [le1, ri1)
 * @param le2,ri2 second substring [le2, ri2)
 * @returns a value `cmp` where:
 *     - cmp < 0 iff s.substr(le1, ri1 - le1) < s.substr(le2, ri2 - le2)
 *     - cmp = 0 iff s.substr(le1, ri1 - le1) = s.substr(le2, ri2 - le2)
 *     - cmp > 0 iff s.substr(le1, ri1 - le1) > s.substr(le2, ri2 - le2)
 * @time O(1)
 * @space O(1)
 */
inline int cmp_substrs(int le1, int ri1, int le2, int ri2) {
  assert(0 <= le1 && le1 <= ri1 && ri1 <= n);
  assert(0 <= le2 && le2 <= ri2 && ri2 <= n);
  int len1 = ri1 - le1;
  int len2 = ri2 - le2;
  return len_lcp(le1, le2) >= min(len1, len2) ? len1 - len2 : sa_inv[le1] - sa_inv[le2];
}
