int walk(int l, int r, const auto& f) {
  l += n, r += n;
  if (T x = s[l]; f(x))
    for (l++; l <= r;) {
      int v = __lg(min(l & -l, r - l + 1));
      if (T y = op(x, s[l >> v]); f(y)) l += 1 << v, x = y;
      else r = l + (1 << v) - 2;
    }
  return l - n;
}
