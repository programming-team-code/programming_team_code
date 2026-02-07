int go(int l, int r) {
//return __lg(min(l & -l, r - l + 1));
//return __lg(min((l + n) & -(l + n), r - l + 1));
  return min(__builtin_ctz(l + n), __lg(r - l + 1));
}
int walk(int l, int r, const auto& f) {
  /*
  for (l += n, r += n; l <= r;)
    if (int u = nxt(l, r); f(s[u])) {
      while (u < n)
        if (f(s[2 * u])) u *= 2;
        else (u *= 2)++;
      return u - n;
    }
  */
  while (l <= r) {
    int u = l + n, x = __lg(min(u & -u, r - l));
    if (f(s[u >> x])) r = l + (1 << x) - 1;
    else l += 1 << x;
  }
  return -1;
}
