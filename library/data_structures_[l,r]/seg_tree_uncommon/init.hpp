#pragma once
tree(const vector<T>& a, F op):
  n(sz(a)), op(op), s(2 * n) {
  rep(i, 0, n) s[i + n] = a[i];
  for (int i = n; --i;) s[i] = op(s[2 * i], s[2 * i + 1]);
}
