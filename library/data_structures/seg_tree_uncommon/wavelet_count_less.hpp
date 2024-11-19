#pragma once
//! Requires ub >= 0
//! count of i in [l..r) such that a[i] < ub
//! @time O(log(max_val))
//! @space O(1)
int count(int l, int r, ull ub) {
  int res = 0;
  for (int h = sz(bv); h--;) {
    int l0 = bv[h].cnt0(l), r0 = bv[h].cnt0(r);
    if ((~ub >> h) & 1) l = l0, r = r0;
    else
      res += r0 - l0, l += bv[h].cnt0(n) - l0,
        r += bv[h].cnt0(n) - r0;
  }
  return res;
}
