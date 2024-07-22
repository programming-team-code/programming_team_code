/** @file */
#pragma once
/**
 * @param u,v 2 nodes
 * @returns 1 iff v is in u's subtree
 * @time O(1)
 * @space O(1)
 */
inline bool in_subtree(int u, int v) {
  if ((t[u].asc & t[v].asc) != t[u].asc) return 0;
  if (auto k = t[v].asc ^ t[u].asc; k) k = bit_floor(k), v = t[head[(t[v].label & -k) | k]].p;
  return t[u].label == t[v].label && t[u].d <= t[v].d;
}
