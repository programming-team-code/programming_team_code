void walk(auto f) {
  int64_t sum = 0;
  for (int i = bit_floor(size(s)), r = 0; i; i /= 2)
    if (r + i <= ssize(s) && f(r + i, sum + s[r + i - 1])) sum += s[(r += i) - 1];
}
