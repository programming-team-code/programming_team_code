/** @file */
#pragma once
#include "in_subtree.hpp"
/**
 * @see https://codeforces.com/blog/entry/71567?#comment-559285
 * @code{.cpp}
       LCA lc(adj);
       int u, v; //to loop over all nodes (except v) on path from u to v:
       for (int i = u; i != v; i = lc.next_on_path(i, v)) {}
 * @endcode
 * @param u,v endpoint nodes of path
 * @returns the node vector<int>({u,p[u],..,lca(u,v),..,p[v],v})[1]
 * @time O(1)
 * @space O(1)
 */
inline int next_on_path(int u, int v) {
  assert(u != v);
  return in_subtree(u, v) ? rmq.query(in[u] + 1, in[v] + 1) : p[u];
}
