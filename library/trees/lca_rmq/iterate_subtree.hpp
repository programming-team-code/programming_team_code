#pragma once
#include "lca_rmq.hpp"
//! https://codeforces.com/blog/entry/44351
//! @time O(size of v's subtree)
//! @space O(1)
rep(k, lc.t[v].in, lc.t[v].in + lc.t[v].sub_sz) {
  int u = lc.rmq.dp[0][k];
