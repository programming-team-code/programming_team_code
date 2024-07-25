/** @file */
#pragma once
RMQ<int, function<int(int, int)>> rmq = {};
/**
 * @param i1,i2 defines substrings [i1, n), [i2, n)
 *      - passing i1,i2 = n is okay
 *      - if one of the suffixes is the entire string (i1 == 0 || i2 == 0) then
 *        it's the same as z algorithm
 * @returns max integer k such that s.substr(i1, k) == s.substr(i2, k)
 * @time O(1)
 * @space O(1)
 */
int len_lcp(int i1, int i2) {
  if (i1 > i2) swap(i1, i2);
  assert(0 <= i1 && i2 <= n);
  if (i1 == i2 || i2 == n) return n - i2;
  if (empty(rmq.dp)) rmq = {lcp, [](int x, int y) { return min(x, y); }};
  auto [le, ri] = minmax(sa_inv[i1], sa_inv[i2]);
  return rmq.query(le, ri);
}
