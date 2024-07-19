/** @file */
#pragma once
#include "lca_rmq.hpp"
/**
 * @see https://codeforces.com/blog/entry/44351
 * @code{.cpp}
       LCA lc(adj); //required
 * @endcode
 * @param u some node
 * @time O(size of u's subtree)
 * @space O(1)
 */
rep(k, lc.t[u].in, lc.t[u].in + lc.t[u].sub_sz) {
  int v = rmq.dp[0][k];
