int walk(int l, int r, const auto& f) {
  while (T x = unit; l < r) {
    int u = l + n, v = __lg(min(u & -u, r - l));
    if (T y = op(x, s[u >> v]); f(y)) x = y, l += 1 << v;
    else r = l + (1 << v) - 1;
  }
  return l;
}
