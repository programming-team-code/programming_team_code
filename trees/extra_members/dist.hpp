int dist(int u, int v) {
  return d[u] + d[v] - 2 * d[lca(u, v)];
}
