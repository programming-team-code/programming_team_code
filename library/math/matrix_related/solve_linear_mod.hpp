/** @file */
#pragma once
#include "row_reduce.hpp"
/**
 * Solves mat * x = b under prime mod. Number of unique solutions = (size of
 * domain) ^ (# of free variables). (# of free variables) is generally
 * equivalent to m - rank.
 *
 * @code{.cpp}
       auto [rank, det, x] = solve_linear_mod(mat, b);
 * @endcode
 */
struct solve_linear_mod {
  int rank; /**< max number of linearly independent vectors */
  int64_t det; /**< determinant */
  vector<int64_t> x; /**< solution vector, empty iff no solution */
  /**
   * @param mat n (rows) by m (cols) matrix; left in reduced row echelon form
   * @param b length n column vector
   * @time O(n * m * min(n, m))
   * @space besides the O(n * m) `mat` param, this allocates/returns a
   * O(m) solution vector
   */
  solve_linear_mod(vector<vector<int64_t>>& mat, const vector<int64_t>& b) {
    assert(ssize(mat) == ssize(b));
    int n = ssize(mat), m = ssize(mat[0]);
    for (int i = 0; i < n; i++)
      mat[i].push_back(b[i]);
    tie(rank, det) = row_reduce(mat, m);
    if (any_of(begin(mat) + rank, end(mat), [](auto& v) { return v.back(); })) {
      return;  // no solution exists
    }
    x.resize(m);
    int j = 0;
    for_each(begin(mat), begin(mat) + rank, [&](auto& v) {
      while (v[j] == 0) j++;
      x[j] = v.back();
    });
  }
};
