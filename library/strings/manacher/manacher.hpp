/** @file */
#pragma once
/**
 * s = "baaba"
 *
 * index   1 3 5 7
 * string b a a b a
 * index  0 2 4 6 8
 *
 * @see https://codeforces.com/blog/entry/12143#comment-324162
 * @param s string/vector
 * @returns man[i] = index of beginning of longest palindrome centered at `i`
 *     - substring [man[i], i - man[i] + 1) is longest palindrome centered at `i`
 *     - longest palindrome centered at `i` has length = i - 2 * man[i] + 1
 *     - substring [le, ri) has center (le + ri - 1)
 * @time O(n)
 * @space a O(n) vector is allocated and returned
 */
template <class T> vector<int> manacher(const T& s) {
	int n = ssize(s);
	vector<int> man(max(0, 2 * n - 1));
	for (int i = 0, p = 0; i < 2 * n - 1; i++) {
		int ri = i <= 2 * (p - man[p]) ? p - max(man[2 * p - i], man[p]) : i / 2;
		man[i] = i - ri;
		while (man[i] > 0 && ri + 1 < n && s[man[i] - 1] == s[ri + 1])
			man[i]--, ri++, p = i;
	}
	return man;
}
