/** @file */
#pragma once
/**
 * @code{.cpp}
       int u, v; //to loop over all nodes (except v) on path from u to v:
       for (int i = u; i != v; i = lin_lca.next_on_path(i, v)) {}
 * @endcode
 * @param u,v endpoint nodes of path
 * @returns the node vi({u,p[u],..,lca(u,v),..,p[v],v})[1]
 * @time O(1)
 * @space O(1)
 */
int next_on_path(int u, int v) {
  assert(u != v);
  if ((t[u].asc & t[v].asc) != t[u].asc) return t[u].p;
  if (t[u].asc != t[v].asc) {
    auto k = bit_floor(t[u].asc ^ t[v].asc);
    v = head[(t[v].label & -k) | k];
  }
  if (t[u].label != t[t[v].p].label || t[u].d >= t[v].d) return t[u].p;
  return t[v].p == u ? v : t[u].big_ch;
}
