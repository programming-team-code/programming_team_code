constexpr int mod = 998244353;
//! https://github.com/kth-competitive-programming/kactl/blob/main/content/number-theory/ModularArithmetic.h
//! https://codeforces.com/blog/entry/122714
struct mint {
  int x;
  mint(int xx = 0): x(xx < 0 ? xx + mod : xx) {}
  mint operator+(mint b) { return x - mod + b.x; }
  mint operator-(mint b) { return x - b.x; }
  mint operator*(mint b) { return int64_t(x) * b.x % mod; }
  mint operator/(mint b) {
    int m = mod, u = 1, v = 0;
    while (m)
      u = exchange(v, u - b.x / m * v),
      b.x = exchange(m, b.x % m);
    assert(b.x == 1);
    return *this * u;
  }
};
//! @code
//!   auto [rank, det] = row_reduce(mat, cols);
//! @endcode
//! columns [0,cols) of mat represent a matrix
//! columns [cols,m) of mat are also
//!   affected by row operations
//! @time O(n * m * min(cols, n))
//! @space O(1)
pair<int, mint> row_reduce(vector<vector<mint>>& mat,
  int cols) {
  int n = ssize(mat), m = ssize(mat[0]), rank = 0;
  mint det = 1;
  for (int col = 0; col < cols && rank < n; col++) {
    auto it = find_if(rank + begin(mat), end(mat),
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
    for (int i = 0; i < n; i++)
      if (i != rank && mat[i][col].x != 0) {
        mint num = mat[i][col];
        for (int j = 0; j < m; j++)
          mat[i][j] = mat[i][j] - mat[rank][j] * num;
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
  int rank;
  mint det;
  vector<mint> sol;
  solve_linear_mod(vector<vector<mint>>& mat,
    const vector<mint>& rhs) {
    int n = ssize(mat), m = ssize(mat[0]);
    for (int i = 0; i < n; i++) mat[i].push_back(rhs[i]);
    tie(rank, det) = row_reduce(mat, m);
    if (any_of(rank + begin(mat), end(mat),
          [](auto& v) { return v.back().x; })) {
      return;
    }
    sol.resize(m);
    int j = 0;
    for_each(begin(mat), begin(mat) + rank, [&](auto& v) {
      while (v[j].x == 0) j++;
      sol[j] = v.back();
    });
  }
};
