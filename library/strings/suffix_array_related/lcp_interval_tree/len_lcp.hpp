/** @file */
#pragma once
/**
 * @param u node
 * @returns length of longest common prefix of u's interval
 * @time O(1)
 * @space O(1)
 */
inline int len_lcp(int u) {
	return u < sf_a.n - 1 ? sf_a.lcp[u] : sf_a.n - sf_a.sa[u - sf_a.n + 1];
}
