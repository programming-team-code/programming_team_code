/** @file */
/**
 * @param u,v endpoint nodes of path
 * @returns number of edges on path
 * @time same as lca(u, v)
 * @space O(1)
 */
inline int dist_edges(int u, int v) {
  return d[u] + d[v] - 2 * d[lca(u, v)];
}
