//! Requires s[i] >= 0
//! max r such that sum of [0,r) < sum, or -1
int walk(ll sum) {
  if (sum <= 0) return -1;
  int r = 0;
  for (int pw = bit_floor(size(s)); pw; pw >>= 1)
    if (r + pw <= sz(s) && s[r + pw - 1] < sum)
      sum -= s[(r += pw) - 1];
  return r;
}
