int walk(int l, int r, const auto& f) {
  while (l <= r) {
    int u = l + n, x = __lg(min(u & -u, r - l + 1));
    if (f(s[u >> x])) r = l + (1 << x) - 2;
    else l += 1 << x;
  }
  return l;
}
