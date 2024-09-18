#pragma once
//! @param num integer
//! @returns number of occurances of num in the multiset
//! @time O(mx_bit)
//! @space O(1)
int count(T num) {
  int v = 0;
  for (int bit = mx_bit; bit >= 0; bit--) {
    bool b = (num >> bit) & 1;
    if (t[v].next[b] == -1) return 0;
    v = t[v].next[b];
  }
  return t[v].sub_sz;
}
