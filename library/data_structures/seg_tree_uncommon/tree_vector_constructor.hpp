#pragma once
tree(const vector<T>& a, T unit, F op):
  n(sz(a)), unit(unit), op(op), s(2 * n) {
  rep(i, 0, n) s[i + n] = a[i];
  for (int i = n - 1; i > 0; i--)
    s[i] = op(s[2 * i], s[2 * i + 1]);
}
