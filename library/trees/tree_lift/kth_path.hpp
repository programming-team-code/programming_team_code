#pragma once
//! returns the node vi({u,p[u],..,lca(u,v),..,p[v],v})[k]
//! @time same as lca(u, v), kth_par(u, k)
//! @space O(1)
int kth_path(int u, int v, int k) {
  int lca_d = t[lca(u, v)].d;
  int u_lca = t[u].d - lca_d;
  int v_lca = t[v].d - lca_d;
  if (k <= u_lca) return kth_par(u, k);
  if (k <= u_lca + v_lca)
    return kth_par(v, u_lca + v_lca - k);
  return -1;
}
