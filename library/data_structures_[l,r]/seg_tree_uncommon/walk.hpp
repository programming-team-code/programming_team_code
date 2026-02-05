T walk(int l, int r, const auto& f) {
  for (l += n, r += n; l <= r;)
    if (int u = nxt(l, r); f(s[u])) {
      while (u < n)
        if (f(s[2 * u])) u = 2 * u;
        else u = 2 * u + 1;
      return u - n;
    }
  return -1;
}
