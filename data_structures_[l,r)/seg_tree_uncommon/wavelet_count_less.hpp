//! count of i in [l..r) such that a[i] < ub
//! @time O(lg)
//! @space O(1)
int count(int l, int r, int64_t ub) {
  int res = 0;
  for (int h = ssize(bv); h--;) {
    int x = bv[h].cnt(l), y = bv[h].cnt(r);
    if ((ub >> h) & 1)
      res += y - x, l += bv[h].cnt(n) - x,
        r += bv[h].cnt(n) - y;
    else l = x, r = y;
  }
  return res;
}
