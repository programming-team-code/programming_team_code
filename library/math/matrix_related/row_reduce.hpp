/** @file */
#pragma once
#include "../binary_exponentiation_mod.hpp"
/**
 * @code{.cpp}
       auto [rank, det] = row_reduce(mat, sz(mat[0]));
 * @endcode
 * @param mat,cols columns [0,cols) of mat represent a matrix, columns [cols,m)
 * are also affected by row operations.
 * @returns pair(rank, determinant)
 * @time O(n * m * min(cols, n))
 * @space besides the O(n * m) `mat` param, this function uses O(1) space
 */
pair<int, ll> row_reduce(vector<vector<ll>>& mat, int cols) {
  int n = sz(mat), m = sz(mat[0]), rank = 0;
  ll det = 1;
  assert(cols <= m);
  for (int col = 0; col < cols && rank < n; col++) {
    auto it = find_if(rank + all(mat), [&](auto& v) { return v[col]; });
    if (it == end(mat)) {
      det = 0;
      continue;
    }
    if (it != begin(mat) + rank) {
      det = det == 0 ? 0 : mod - det;
      iter_swap(begin(mat) + rank, it);
    }
    det = det * mat[rank][col] % mod;
    ll a_inv = bin_exp(mat[rank][col], mod - 2);
    for (ll& num : mat[rank]) num = num * a_inv % mod;
    rep(i, 0, n) if (i != rank && mat[i][col] != 0) {
      ll num = mat[i][col];
      rep(j, 0, m) {
        mat[i][j] -= mat[rank][j] * num % mod;
        if (mat[i][j] < 0) mat[i][j] += mod;
      }
    }
    rank++;
  }
  return {rank, det};
}
