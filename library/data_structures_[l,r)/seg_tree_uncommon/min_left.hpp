int min_left(int l, int r, const auto& f) {
  for (T x = unit; l < r;) {
    int u = r + n, v = __lg(min(u & -u, r - l));
    if (T y = op(s[(u - 1) >> v], x); f(y))
      r -= 1 << v, x = y;
    else l = r - (1 << v) + 1;
  }
  return r;
}
