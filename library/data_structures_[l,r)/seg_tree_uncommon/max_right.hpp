int max_right(int l, int r, auto f) {
  for (T x = unit; l < r;) {
    int u = l + n, v = bit_width(min(u & -u, r - l) / 2u),
        m = l + (1 << v);
    if (T y = op(x, s[u >> v]); f(m, y)) l = m, x = y;
    else r = m - 1;
  }
  return l;
}
