//! @file
/**
 * @param u,v 2 nodes
 * @returns 1 iff v is in u's subtree
 * @time O(1)
 * @space O(1)
 */
bool in_subtree(int u, int v) {
  return t[u].in <= t[v].in && t[v].in < t[u].in + t[u].sub_sz;
}
