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
  assert(cols <= m);
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
