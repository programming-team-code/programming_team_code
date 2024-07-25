/** @file */
#pragma once
/**
 * Requires bit.sum(i, i + 1) >= 0 and sum > 0
 * @param sum see return
 * @returns max pos such that sum of range [0, pos) < sum
 * @time O(log n)
 * @space O(1)
 */
int lower_bound(T sum) {
  assert(sum > 0);
  int pos = 0;
  for (int pw = 1 << __lg(sz(s) | 1); pw; pw >>= 1)
    if (pos + pw <= sz(s) && s[pos + pw - 1] < sum)
      pos += pw, sum -= s[pos - 1];
  return pos;
}
