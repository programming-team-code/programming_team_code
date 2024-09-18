#pragma once
//! @param v node
//! @returns length of longest common prefix of v's
//! interval/range
//! @time O(1)
//! @space O(1)
int len_lcp_range(int v) {
  return v < sf_a.n - 1 ? sf_a.lcp[v]
                        : sf_a.n - sf_a.sa[v - sf_a.n + 1];
}
