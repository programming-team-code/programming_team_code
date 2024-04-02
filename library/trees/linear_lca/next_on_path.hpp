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
inline int next_on_path(int u, int v) {
  assert(u != v);
  if ((asc[u] & asc[v]) != asc[u]) return p[u];
  if (asc[u] != asc[v]) {
    auto k = bit_floor(asc[u] ^ asc[v]);
    v = head[(label[v] & -k) | k];
  }
  if (label[u] != label[p[v]] || d[u] >= d[v]) return p[u];
  return p[v] == u ? v : big_ch[u];
}
