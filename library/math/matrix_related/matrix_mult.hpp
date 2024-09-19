#pragma once
//! https://codeforces.com/blog/entry/80195
//! @code
//!   auto c = a * b;
//! @endcode
//! @time O(n * m * inner)
//! @space O(n * m)
template<class T>
vector<vector<T>> operator*(const vector<vector<T>>& a,
  const vector<vector<T>>& b) {
  int n = sz(a), m = sz(b[0]), inner = sz(b);
  vector<vector<T>> c(n, vector<T>(m));
  rep(i, 0, n) rep(k, 0, inner) rep(j, 0, m) c[i][j] +=
    a[i][k] * b[k][j];
  return c;
}
