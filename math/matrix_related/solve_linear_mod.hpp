const int mod = 998244353;
/**
 * @see https://github.com/kth-competitive-programming/kactl /blob/main/content/number-theory/ModularArithmetic.h
 * @see https://codeforces.com/blog/entry/122714
 */
struct mint {
  int x;
  mint(int xx = 0) : x(xx < 0 ? xx + mod : xx) {}
  mint operator+(mint b) { return x - mod + b.x; }
  mint operator-(mint b) { return x - b.x; }
  mint operator*(mint b) { return int64_t(x) * b.x % mod; }
  mint operator/(mint b) {
    int m = mod, u = 1, v = 0;
    while (m) u = exchange(v, u - b.x / m * v), b.x = exchange(m, b.x % m);
    assert(b.x == 1);
    return *this * u;
  }
};
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
pair<int, mint> row_reduce(vector<vector<mint>>& mat, int cols) {
  int n = (int)size(mat), m = (int)size(mat[0]), rank = 0;
  mint det = 1;
  for (int col = 0; col < cols && rank < n; col++) {
    auto it = find_if(rank + begin(mat), end(mat), [&](auto& v) { return v[col].x; });
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
    for (int i = 0; i < (n); i++)
      if (i != rank && mat[i][col].x != 0) {
        mint num = mat[i][col];
        for (int j = 0; j < (m); j++) mat[i][j] = mat[i][j] - mat[rank][j] * num;
      }
    rank++;
  }
  return {rank, det};
}
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
  mint det; /**< determinant */
  vector<mint> x; /**< solution vector, empty iff no solution */
  /**
   * @param mat n (rows) by m (cols) matrix; left in reduced row echelon form
   * @param b length n column vector
   * @time O(n * m * min(n, m))
   * @space besides the O(n * m) `mat` param, this allocates/returns a
   * O(m) solution vector
   */
  solve_linear_mod(vector<vector<mint>>& mat, const vector<mint>& b) {
    int n = (int)size(mat), m = (int)size(mat[0]);
    for (int i = 0; i < (n); i++) mat[i].push_back(b[i]);
    tie(rank, det) = row_reduce(mat, m);
    if (any_of(rank + begin(mat), end(mat), [](auto& v) { return v.back().x; })) {
      return;  // no solution exists
    }
    x.resize(m);
    int j = 0;
    for_each(begin(mat), begin(mat) + rank, [&](auto& v) {
      while (v[j].x == 0) j++;
      x[j] = v.back();
    });
  }
};
