int dist_edges(int u, int v) {
  return t[u].d + t[v].d - 2 * t[lca(u, v)].d;
}
