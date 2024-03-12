/** @file */
#pragma once
/**
 * @see https://codeforces.com/blog/entry/80195
 *
 * @param a,b binary matrices
 * @returns a*b mod 2
 * @time O(n * m * inner / w) where w is the machine word size (usually 32 or
 * 64)
 * @space besides the O(n * inner) and O(inner * m) params, this function
 * allocates and returns a O(n * m) vector
 */
template <unsigned long int N>
array<bitset<N>, N> operator*(const array<bitset<N>, N>& a,
                              const array<bitset<N>, N>& b) {
	array<bitset<N>, N> c;
	for (auto i = 0; i < N; i++)
		for (auto j = 0; j < N; j++)
			if (a[i][j]) c[i] ^= b[j];
	return c;
}
