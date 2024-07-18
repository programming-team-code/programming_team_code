/** @file */
#pragma once
/**
 * @param num integer
 * @returns integer x such that x is in this multiset, and the number of
 * (x^num) is minimum.
 * @time O(mx_bit)
 * @space O(1)
 */
T walk(T num) {
  assert(t[0].sub_sz > 0);
  T res = 0;
  for (int u = 0, bit = mx_bit; bit >= 0; bit--) {
    bool b = (num >> bit) & 1;
    int v = t[u].next[b];
    if (v != -1 && t[v].sub_sz > 0)
      u = v, res |= T(b) << bit;
    else
      u = t[u].next[!b], res |= T(!b) << bit;
  }
  return res;
}
