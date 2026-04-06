void walk(auto f) {
  ll sum = 0;
  for (int i = bit_floor(size(s)), r = 0; i; i /= 2)
    if (r + i <= sz(s) && f(r + i - 1, sum + s[r + i - 1]))
      sum += s[(r += i) - 1];
}
