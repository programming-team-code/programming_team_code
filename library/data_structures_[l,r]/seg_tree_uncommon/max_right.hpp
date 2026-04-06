void max_right(int l, int r, auto f) {
  if (T x = s[l + n]; f(l, x))
    for (l++; l <= r;) {
      int u = l + n, v = __lg(min(u & -u, r - l + 1)),
          m = l + (1 << v) - 1;
      if (T y = op(x, s[u >> v]); f(m, y))
        l = m + 1, x = y;
      else r = m - 1;
    }
}
