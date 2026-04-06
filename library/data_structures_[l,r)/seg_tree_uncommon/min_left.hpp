void min_left(int l, int r, auto f) {
  for (T x = unit; l < r;) {
    int u = r + n, v = __lg(min(u & -u, r - l)),
        m = r - (1 << v);
    if (T y = op(s[(u - 1) >> v], x); f(m, y))
      r = m, x = y;
    else l = m + 1;
  }
}
