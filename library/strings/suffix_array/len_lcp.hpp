/** @file */
#pragma once
RMQ<int, function<int(int, int)>> rmq = {{}, nullptr};
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
  if (int mx = max(i1, i2); i1 == i2 || mx == n) return n - mx;
  if (empty(rmq.dp[0])) rmq = {lcp, [](int x, int y) { return min(x, y); }};
  auto [le, ri] = minmax(sa_inv[i1], sa_inv[i2]);
  return rmq.query(le, ri);
}
