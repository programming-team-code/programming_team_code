/** @file */
#pragma once
/**
 * @param val integer
 * @returns number of occurances of val in the multiset
 * @time O(mx_bit)
 * @space O(1)
 */
int count(T val) {
  int u = 0;
  for (int bit = mx_bit; bit >= 0; bit--) {
    bool b = (val >> bit) & 1;
    if (t[u].next[b] == -1) return 0;
    u = t[u].next[b];
  }
  return t[u].sub_sz;
}
