#pragma once
#include "../mod_division.hpp"
//! @code
//!   auto [rank, det] = row_reduce(mat, cols);
//! @endcode
//! columns [0,cols) of mat represent a matrix
//! columns [cols,m) of mat are also
//!   affected by row operations
//! @time O(n * m * min(cols, n))
//! @space O(1)
pii row_reduce(vector<vi>& mat, int cols) {
  int n = sz(mat), m = sz(mat[0]), rank = 0;
  int det = 1;
  for (int col = 0; col < cols && rank < n; col++) {
    auto it = find_if(rank + all(mat),
      [&](auto& v) { return v[col]; });
    if (it == end(mat)) {
      det = 0;
      continue;
    }
    if (it != begin(mat) + rank) {
      det = (mod - det) % mod;
      iter_swap(begin(mat) + rank, it);
    }
    det = 1LL * det * mat[rank][col] % mod;
    int a_inv = mod_div(1, mat[rank][col]);
    for (int& num : mat[rank])
      num = 1LL * num * a_inv % mod;
    rep(i, 0, n) if (i != rank && mat[i][col] != 0) {
      int num = mat[i][col];
      rep(j, 0, m) mat[i][j] =
        ((mat[i][j] - 1LL * mat[rank][j] * num) % mod +
          mod) %
        mod;
    }
    rank++;
  }
  return {rank, det};
}
