//! https://nor-blog.pages.dev/posts/2023-11-27-std-exchange-cpp/
//! @code
//!   int quotient = mod_div(x, y); // returns x * y^-1
//! @endcode
//! @time O(log(y))
//! @space O(1)
const int mod = 998244353;
int mod_div(int x, int y) {
  int m = mod, u = 1, v = 0;
  while (m) swap(u -= y / m * v, v), swap(y %= m, m);
  assert(y == 1);
  return 1LL * x * (u + mod) % mod;
}
//! @code
//!   auto [rank, det] = row_reduce(mat, cols);
//! @endcode
//! columns [0,cols) of mat represent a matrix
//! columns [cols,m) of mat are also
//!   affected by row operations
//! @time O(n * m * min(cols, n))
//! @space O(1)
pair<int, int> row_reduce(vector<vector<int>>& mat,
  int cols) {
  int n = ssize(mat), m = ssize(mat[0]), rank = 0;
  int det = 1;
  for (int col = 0; col < cols && rank < n; col++) {
    auto it = find_if(rank + begin(mat), end(mat),
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
    for (int i = 0; i < n; i++)
      if (i != rank && mat[i][col] != 0) {
        int num = mat[i][col];
        for (int j = 0; j < m; j++)
          mat[i][j] =
            ((mat[i][j] - 1LL * mat[rank][j] * num) % mod +
              mod) %
            mod;
      }
    rank++;
  }
  return {rank, det};
}
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
    int n = ssize(mat), m = ssize(mat[0]);
    for (int i = 0; i < n; i++) mat[i].push_back(rhs[i]);
    tie(rank, det) = row_reduce(mat, m);
    if (any_of(rank + begin(mat), end(mat),
          [](vector<int>& v) { return v.back(); })) {
      return;
    }
    sol.resize(m);
    int j = 0;
    for_each(begin(mat), begin(mat) + rank,
      [&](vector<int>& v) {
        while (!v[j]) j++;
        sol[j] = v.back();
      });
  }
};
