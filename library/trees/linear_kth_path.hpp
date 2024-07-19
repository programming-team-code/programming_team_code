/** @file */
#pragma once
#include "linear_lca/linear_lca.hpp"
#include "ladder_decomposition/linear_kth_par.hpp"
struct linear_kth_path {
  linear_lca lin_lca;
  linear_kth_par lin_kp;
  linear_kth_path(const vector<vi>& adj) : lin_lca(adj), lin_kp(adj) {}
  /**
   * @param u,v endpoint nodes of path
   * @param k index into path
   * @returns the node vi({u,p[u],..,lca(u,v),..,p[v],v})[k], or -1, so u if k=0
   * @time O(1)
   * @space O(1)
   */
  int kth_path(int u, int v, int k) {
    assert(k >= 0);
    int lca_d = lin_kp.t[lin_lca.lca(u, v)].d;
    int u_lca = lin_kp.t[u].d - lca_d;
    int v_lca = lin_kp.t[v].d - lca_d;
    if (k <= u_lca) return lin_kp.kth_par(u, k);
    if (k <= u_lca + v_lca) return lin_kp.kth_par(v, u_lca + v_lca - k);
    return -1;
  }
};
