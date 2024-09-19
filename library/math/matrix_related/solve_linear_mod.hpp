#pragma once
#include "row_reduce.hpp"
//! @code
//!   auto [rank, det, x] = solve_linear_mod(mat, b);
//! @endcode
//! for each i, 0<=i<n:
//!   b[i] == sum over j of (mat[i][j]*x[j])
//! Number of unique solutions =
//!   (size of domain)^(# of free variables)
//! (# of free variables) = m - rank.
//! @time O(n * m * min(n, m))
//! @space O(m)
struct solve_linear_mod {
  int rank;
  mint det;
  vector<mint> x;
  solve_linear_mod(vector<vector<mint>>& mat,
    const vector<mint>& b) {
    int n = sz(mat), m = sz(mat[0]);
    rep(i, 0, n) mat[i].push_back(b[i]);
    tie(rank, det) = row_reduce(mat, m);
    if (any_of(rank + all(mat),
          [](auto& v) { return v.back().x; })) {
      return;
    }
    x.resize(m);
    int j = 0;
    for_each(begin(mat), begin(mat) + rank, [&](auto& v) {
      while (v[j].x == 0) j++;
      x[j] = v.back();
    });
  }
};
