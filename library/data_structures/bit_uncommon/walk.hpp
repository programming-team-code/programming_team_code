//! Requires bit.s[i] >= 0
//! @returns max pos such that sum of [0,pos) < sum
int walk(ll sum) {
  if (sum <= 0) return -1;
  int pos = 0;
  for (int pw = bit_floor(size(s)); pw; pw >>= 1)
    if (pos + pw <= sz(s) && s[pos + pw - 1] < sum)
      pos += pw, sum -= s[pos - 1];
  return pos;
}
