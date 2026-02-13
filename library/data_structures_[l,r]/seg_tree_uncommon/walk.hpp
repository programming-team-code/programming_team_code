int walk(int l, int r, const auto& f) {
  while (l <= r) {
    int u = l + n, v = __lg(min(u & -u, r - l + 1));
    if (f(s[u >> v])) l += 1 << v;
    else r = l + (1 << v) - 2;
  }
  return l;
}
