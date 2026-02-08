int walk(int l, int r, const auto& f) {
  while (l < r) {
    int u = l + n, x = __lg(min(u & -u, r - l));
    if (f(s[u >> x])) l += 1 << x;
    else r = l + (1 << x) - 1;
  }
  return l;
}
