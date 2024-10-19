#pragma once
//! Requires bit.query(i,i+1) >= 0
//! @returns max pos such that sum of [0,pos) < sum
int lower_bound(ll sum) {
  if (sum <= 0) return -1;
  int pos = 0;
  for (int pw = 1 << __lg(sz(s) | 1); pw; pw >>= 1)
    if (pos + pw <= sz(s) && s[pos + pw - 1] < sum)
      pos += pw, sum -= s[pos - 1];
  return pos;
}
