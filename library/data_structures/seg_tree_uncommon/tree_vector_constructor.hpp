/** @file */
#pragma once
tree(const vector<T>& a, T unit, F f) : n(sz(a)), s(2 * n), unit(unit), f(f) {
  rep(i, 0, n) s[i + n] = a[i];
  for (int i = n - 1; i > 0; i--) s[i] = f(s[2 * i], s[2 * i + 1]);
}
