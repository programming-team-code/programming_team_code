int min_left(int l, int r, auto f) {
  if (T x = s[r + n]; f(r, x))
    for (r--; l <= r;) {
      int u = r + 1 + n, v = __lg(min(u & -u, r - l + 1)), m = r - (1 << v) + 1;
      if (T y = op(s[(u - 1) >> v], x); f(m, y)) r = m - 1, x = y;
      else l = m + 1;
    }
  return r;
}
