/**
 * @see https://codeforces.com/blog/entry/80195
 *
 * @param a,b binary matrices
 * @returns a*b mod 2
 * @time O(n * m * k / w) where w is the machine word size (usually 32 or
 * 64)
 * @space O(N * K / w + N * M / w + M * K / w) where w is the machine word size
 * (usually 32 or 64)
 */
template <unsigned long int N, unsigned long int M, unsigned long int K>
array<bitset<K>, N> operator*(const array<bitset<M>, N>& a,
                              const array<bitset<K>, M>& b) {
  array<bitset<K>, N> c;
  for (int i = 0; i < (int(N)); i++)
    for (int j = 0; j < (int(M)); j++)
      if (a[i][j]) c[i] ^= b[j];
  return c;
}
