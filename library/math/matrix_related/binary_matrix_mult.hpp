#pragma once
//! https://codeforces.com/blog/entry/80195
//! @code
//!   auto c = a * b;
//! @endcode
//! @time O(n*m*k / 64)
//! @space O((n*k + n*m + m*k) / 64)
template<unsigned long int N, unsigned long int M,
  unsigned long int K>
array<bitset<K>, N> operator*(const array<bitset<M>, N>& a,
  const array<bitset<K>, M>& b) {
  array<bitset<K>, N> c;
  rep(i, 0, int(N)) rep(j, 0, int(M)) if (a[i][j]) c[i] ^=
    b[j];
  return c;
}
