/** @file */
#pragma once
/**
 * @param u,v 2 nodes
 * @returns 1 iff v is in u's subtree
 * @time O(1)
 * @space O(1)
 */
inline bool in_subtree(int u, int v) {
	return in[u] <= in[v] && in[v] < in[u] + sub_sz[u];
}
