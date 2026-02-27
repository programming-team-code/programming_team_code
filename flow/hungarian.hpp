//! https://e-maxx.ru/algo/assignment_hungary
//! @code
//!   vector cost(n+1,vector(m+1,(ll)0));
//!   auto [min_weight, l_to_r] = hungarian(cost);
//! @endcode
//! cost[i][j] = edge weight, 1<=i<=n<=m; 1<=j<=m
//! min_weight = sum of edge weights in matching
//! edge v <=> l_to_r[v] is in the matching
//!   1<=v<=n; 1<=l_to_r[v]<=m
//! @time O(n^2 * m)
//! @space O(n + m)
pair<int64_t, vector<int>> hungarian(
  const vector<vector<int64_t>>& cost) {
  int n = ssize(cost), m = ssize(cost[0]);
  vector<int> p(m), way(m);
  vector<int64_t> u(n), v(m);
  for (int i = 1; i < n; i++) {
    p[0] = i;
    int j0 = 0;
    vector minv(m, LLONG_MAX);
    vector<int> used(m);
    do {
      used[j0] = 1;
      int i0 = p[j0], j1 = 0;
      int64_t delta = LLONG_MAX;
      for (int j = 1; j < m; j++)
        if (!used[j]) {
          int64_t cur = cost[i0][j] - u[i0] - v[j];
          if (cur < minv[j]) minv[j] = cur, way[j] = j0;
          if (minv[j] < delta) delta = minv[j], j1 = j;
        }
      for (int j = 0; j < m; j++)
        if (used[j]) u[p[j]] += delta, v[j] -= delta;
        else minv[j] -= delta;
      j0 = j1;
    } while (p[j0] != 0);
    do {
      int j1 = way[j0];
      p[j0] = p[j1];
      j0 = j1;
    } while (j0);
  }
  vector<int> l_to_r(n);
  for (int j = 1; j < m; j++) l_to_r[p[j]] = j;
  return {-v[0], l_to_r};
}
