#pragma once
//! count of i in [l..r) such that a[i] < ub
//! @time O(lg)
//! @space O(1)
int count(int l, int r, ll ub) {
  int res = 0;
  for (int h = sz(bv); h--;) {
    int l0 = bv[h].cnt(l), r0 = bv[h].cnt(r);
    if ((~ub >> h) & 1) l = l0, r = r0;
    else
      res += r0 - l0, l += bv[h].cnt(n) - l0,
        r += bv[h].cnt(n) - r0;
  }
  return res;
}
