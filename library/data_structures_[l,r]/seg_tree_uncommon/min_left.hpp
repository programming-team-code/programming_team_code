int min_left(int l, int r, const auto& f) {
  if (T x = s[r + n]; f(x))
    for (r--; l <= r;) {
      int u = r + 1 + n, v = __lg(min(u & -u, r - l + 1));
      if (T y = op(s[(u - 1) >> v], x); f(y))
        r -= 1 << v, x = y;
      else l = r - (1 << v) + 1;
    }
  return r;
}
