int walk2(ll sum) {
  if (sum <= 0) return -1;
  int r = 0;
  for (int i = bit_floor(size(s)); i; i /= 2)
    if (r + i <= sz(s) && s[r + i - 1] < sum)
      sum -= s[(r += i) - 1];
  return r;
}
