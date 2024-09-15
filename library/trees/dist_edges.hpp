//! @file
/**
 * @param u,v endpoint nodes of path
 * @returns number of edges on path
 * @time same as lca(u, v)
 * @space O(1)
 */
int dist_edges(int u, int v) {
  return t[u].d + t[v].d - 2 * t[lca(u, v)].d;
}
