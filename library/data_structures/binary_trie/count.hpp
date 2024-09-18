#pragma once
int count(T num) {
  int v = 0;
  for (int bit = mx_bit; bit >= 0; bit--) {
    bool b = (num >> bit) & 1;
    if (t[v].next[b] == -1) return 0;
    v = t[v].next[b];
  }
  return t[v].sub_sz;
}
