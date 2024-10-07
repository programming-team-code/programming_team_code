#pragma once
//! https://codeforces.com/blog/entry/112755
//! @code
//!   int tm = split_inc(tl, tr);
//!   // [tl,tr] splits into [tl,tm] and [tm+1,tr]
//! @endcode
int split_inc(int tl, int tr) {
  int pw2 = 1 << __lg(tr - tl + 1);
  return min(tl + pw2 - 1, tr - pw2 / 2);
}
