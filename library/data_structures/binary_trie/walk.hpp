#pragma once
T walk(T num) {
  T res = 0;
  for (int v = 0, bit = mx_bit; bit >= 0; bit--) {
    bool b = (num >> bit) & 1;
    int u = t[v].next[b];
    if (u != -1 && t[u].sub_sz > 0)
      v = u, res |= T(b) << bit;
    else v = t[v].next[!b], res |= T(!b) << bit;
  }
  return res;
}
