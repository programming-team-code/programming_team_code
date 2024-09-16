//! @file
#pragma once
#include "../mod_int.hpp"
//! @code{.cpp}
//!     auto [rank, det] = row_reduce(mat, sz(mat[0]));
//! @endcode
//! @param mat,cols columns [0,cols) of mat represent a
//! matrix, columns [cols,m) are also affected by row
//! operations.
//! @returns pair(rank, determinant)
//! @time O(n * m * min(cols, n))
//! @space besides the O(n * m) `mat` param, this function
//! uses O(1) space
pair<int, mint> row_reduce(vector<vector<mint>>& mat,
                           int cols) {
  int n = sz(mat), m = sz(mat[0]), rank = 0;
  mint det = 1;
  for (int col = 0; col < cols && rank < n; col++) {
    auto it = find_if(rank + all(mat),
                      [&](auto& v) { return v[col].x; });
    if (it == end(mat)) {
      det = 0;
      continue;
    }
    if (it != begin(mat) + rank) {
      det = mint(0) - det;
      iter_swap(begin(mat) + rank, it);
    }
    det = det * mat[rank][col];
    mint a_inv = mint(1) / mat[rank][col];
    for (mint& num : mat[rank]) num = num * a_inv;
    rep(i, 0, n) if (i != rank && mat[i][col].x != 0) {
      mint num = mat[i][col];
      rep(j, 0, m) mat[i][j] =
          mat[i][j] - mat[rank][j] * num;
    }
    rank++;
  }
  return {rank, det};
}
