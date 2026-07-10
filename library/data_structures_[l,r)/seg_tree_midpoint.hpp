#pragma once
//! https://codeforces.com/blog/entry/112755
int split(int tl, int tr) {
  int pw2 = bit_floor(tr - tl + 0u);
  return min(tl + pw2, tr - (pw2 >> 1));
}
