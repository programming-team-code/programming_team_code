void max_right(int l, int r, const auto& f) {
  for (T x = unit; l < r;) {
    int u = l + n, v = __lg(min(u & -u, r - l)),
        m = l + (1 << v);
    if (T y = op(x, s[u >> v]); f(m, y)) l = m, x = y;
    else r = m - 1;
  }
}
