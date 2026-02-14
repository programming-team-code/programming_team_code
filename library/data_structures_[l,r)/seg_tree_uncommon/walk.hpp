int walk(int l, int r, const auto& f) {
  for (T x = unit; l < r;) {
    int u = l + n, v = __lg(min(u & -u, r - l));
    if (T y = op(x, s[u >> v]); f(y)) l += 1 << v, x = y;
    else r = l + (1 << v) - 1;
  }
  return l;
}
