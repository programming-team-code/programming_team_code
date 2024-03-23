const int mod = 998'244'353;
/**
 * @see https://github.com/kth-competitive-programming/kactl /blob/main/content/number-theory/ModPow.h
 * @param b base
 * @param e exponent
 * @returns (b^e)%mod, 1 for 0^0.
 * @time O(log e)
 * @space O(1)
 */
int64_t bin_exp(int64_t b, int64_t e) {
  assert(0 <= e);
  auto res = 1LL;
  if ((b %= mod) < 0) b += mod;
  for (; e; b = b * b % mod, e /= 2)
    if (e & 1) res = res * b % mod;
  return res;
}
/**
 * @code{.cpp}
       auto [rank, det] = row_reduce(mat, ssize(mat[0]));
 * @endcode
 * @param mat,cols columns [0,cols) of mat represent a matrix, columns [cols,m)
 * are also affected by row operations.
 * @returns pair(rank, determinant)
 * @time O(n * m * min(cols, n))
 * @space besides the O(n * m) `mat` param, this function uses O(1) space
 */
pair<int, int64_t> row_reduce(vector<vector<int64_t>>& mat, int cols) {
  int n = ssize(mat), m = ssize(mat[0]), rank = 0;
  auto det = 1LL;
  assert(cols <= m);
  for (int col = 0; col < cols && rank < n; col++) {
    auto it = find_if(begin(mat) + rank, end(mat), [&](auto& v) { return v[col]; });
    if (it == end(mat)) {
      det = 0;
      continue;
    }
    if (it != begin(mat) + rank) {
      det = det == 0 ? 0 : mod - det;
      iter_swap(begin(mat) + rank, it);
    }
    det = det * mat[rank][col] % mod;
    auto a_inv = bin_exp(mat[rank][col], mod - 2);
    for (auto& val : mat[rank]) val = val * a_inv % mod;
    for (int i = 0; i < n; i++)
      if (i != rank && mat[i][col] != 0) {
        auto val = mat[i][col];
        for (int j = 0; j < m; j++) {
          mat[i][j] -= mat[rank][j] * val % mod;
          if (mat[i][j] < 0) mat[i][j] += mod;
        }
      }
    rank++;
  }
  return {rank, det};
}
