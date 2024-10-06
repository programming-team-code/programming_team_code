#pragma once
//! https://codeforces.com/blog/entry/112755
int split_inc(int tl, int tr) {
  int pw2 = 1 << __lg(tr - tl + 1);
  return min(tl + pw2 - 1, tr - pw2 / 2);
}
