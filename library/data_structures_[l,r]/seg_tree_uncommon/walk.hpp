int walk(int l, int r, const auto& f) {
  if (T x = s[l + n]; f(x))
    for (l++; l <= r;) {
      int u = l + n, v = __lg(min(u & -u, r - l + 1));
      if (T y = op(x, s[u >> v]); f(y)) l += 1 << v, x = y;
      else r = l + (1 << v) - 2;
    }
  return l;
}
