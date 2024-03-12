/** @file */
#pragma once
/**
 * @see https://codeforces.com/blog/entry/80195
 *
 * @param a,b binary matrices
 * @returns a*b mod 2
 * @time O(n * m * k / w) where w is the machine word size (usually 32 or
 * 64)
 * @space besides the O(n * inner) and O(inner * m) params, this function
 * allocates and returns a O(n * m) vector
 */
template <unsigned long int N, unsigned long int M, unsigned long int K>
array<bitset<K>, N> operator*(const array<bitset<M>, N>& a,
                              const array<bitset<K>, M>& b) {
	array<bitset<K>, N> c;
	for (unsigned long int i = 0; i < N; i++)
		for (unsigned long int j = 0; j < M; j++)
			if (a[i][j]) c[i] ^= b[j];
	return c;
}
