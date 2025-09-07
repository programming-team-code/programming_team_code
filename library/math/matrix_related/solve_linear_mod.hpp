#pragma once
#include "row_reduce.hpp"
//! @code
//!   auto [rank, det, sol] = solve_linear_mod(mat, rhs);
//! @endcode
//! for each i, 0<=i<n:
//!   rhs[i] == sum over j of (mat[i][j]*sol[j])
//! Number of unique solutions =
//!   (size of domain)^(# of free variables)
//! (# of free variables) = m - rank.
//! @time O(n * m * min(n, m))
//! @space O(m)
struct solve_linear_mod {
  int rank, det;
  vector<int> sol;
  solve_linear_mod(vector<vector<int>>& mat,
    const vector<int>& rhs) {
    int n = sz(mat), m = sz(mat[0]);
    rep(i, 0, n) mat[i].push_back(rhs[i]);
    tie(rank, det) = row_reduce(mat, m);
    if (any_of(rank + all(mat),
          [](vi& v) { return v.back(); })) {
      return;
    }
    sol.resize(m);
    int j = 0;
    for_each(begin(mat), begin(mat) + rank, [&](vi& v) {
      while (!v[j]) j++;
      sol[j] = v.back();
    });
  }
};
