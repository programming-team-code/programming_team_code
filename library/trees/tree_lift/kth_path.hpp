/** @file */
#pragma once
/**
 * @param u,v endpoint nodes of path
 * @param k index into path
 * @returns the node vi({u,p[u],..,lca(u,v),..,p[v],v})[k], or -1, so u if k=0
 * @time same as lca(u, v), kth_par(u, k)
 * @space O(1)
 */
inline int kth_path(int u, int v, int k) {
  assert(k >= 0);
  int lca_d = d[lca(u, v)];
  int u_lca = d[u] - lca_d;
  int v_lca = d[v] - lca_d;
  if (k <= u_lca) return kth_par(u, k);
  if (k <= u_lca + v_lca) return kth_par(v, u_lca + v_lca - k);
  return -1;
}
