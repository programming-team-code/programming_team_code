int min_left(int l, int r, const auto& f) {
  if (T x = s[r + n]; f(x))
    while (l < r) {
      int u = r + n, v = __lg(min(u & -u, r - l));
      if (T y = op(s[(u - 1) >> v], x); f(y))
        r -= 1 << v, x = y;
      else l = r - (1 << v) + 1;
    }
  return l;
}
