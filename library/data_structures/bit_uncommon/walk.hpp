//! Requires sum of [i,i] >= 0
//! Returns min r st sum of [0,r] >= sum
//! Returns n if sum of [0,n-1] < sum
int walk(ll sum) {
  if (sum <= 0) return -1;
  int r = 0;
  for (int i = bit_floor(size(s)); i; i /= 2)
    if (r + i <= sz(s) && s[r + i - 1] < sum)
      sum -= s[(r += i) - 1];
  return r;
}
