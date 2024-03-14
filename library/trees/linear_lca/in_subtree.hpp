/** @file */
#pragma once
/**
 * @param u,v 2 nodes
 * @returns 1 iff v is in u's subtree
 * @time O(1)
 * @space O(1)
 */
inline bool in_subtree(int u, int v) {
  if ((asc[u] & asc[v]) != asc[u]) return 0;
  v = lift(v, asc[u]);
  return label[u] == label[v] && d[u] <= d[v];
}
