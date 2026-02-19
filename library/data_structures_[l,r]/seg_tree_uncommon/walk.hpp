int walk(int l, int r, const auto& f) {
  bool initialized = 0;
  T x;
  while (l <= r) {
    int u = l + n, v = __lg(min(u & -u, r - l + 1));
    T y = initialized ? op(x, f(s[u >> v])) : s[u >> v];
    if (f(y)) l += 1 << v, x = y, initialized = 1;
    else r = l + (1 << v) - 2;
  }
  return l;
}
