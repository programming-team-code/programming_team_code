//! Requires bit.query(i,i+1) >= 0
//! @returns max pos such that sum of [0,pos) < sum
int lower_bound(int64_t sum) {
  if (sum <= 0) return -1;
  int pos = 0;
  for (int pw = 1 << __lg(ssize(s) | 1); pw; pw >>= 1)
    if (pos + pw <= ssize(s) && s[pos + pw - 1] < sum)
      pos += pw, sum -= s[pos - 1];
  return pos;
}
