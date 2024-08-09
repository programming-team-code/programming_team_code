/**
 * @see https://e-maxx.ru/algo/assignment_hungary
 * @code{.cpp}
       auto [min_weight, l_to_r] = hungarian(cost);
 * @endcode
 * Calculates a matching: number of edges is maximized, but since it's a
 * complete bipartite graph with n <= m, this matching always has size n. Of
 * all ways to do this, sum of edge weights is minimized.
 */
struct hungarian {
  int64_t min_weight; /**< sum of edge weights in matching */
  vector<int> l_to_r; /**< edge v <=> l_to_r[v] is in the matching, 1<=v<=n; 1<=l_to_r[v]<=m */
  /**
   * @param cost (n+1)-by-(m+1) array: cost[u][v] = weight (can be negative) of
   * the edge u <=> v, 1<=u<=n; 1<=v<=m, n<=m
   * @time O(n^2 * m)
   * @space besides the O(n * m) `cost` param, this allocates `l_to_r`
   * which is O(n), and various O(m) arrays are also allocated temporarily
   */
  hungarian(const vector<vector<int64_t>>& cost) : l_to_r((int)size(cost)) {
    int n = (int)size(cost) - 1, m = (int)size(cost[0]) - 1;
    vector<int> p(m + 1), way(m + 1);
    vector<int64_t> u(n + 1), v(m + 1);
    for (int i = 1; i < (n + 1); i++) {
      p[0] = i;
      int j0 = 0;
      vector minv(m + 1, LLONG_MAX);
      vector<bool> used(m + 1);
      do {
        used[j0] = 1;
        int i0 = p[j0], j1 = 0;
        int64_t delta = LLONG_MAX;
        for (int j = 1; j < (m + 1); j++)
          if (!used[j]) {
            int64_t cur = cost[i0][j] - u[i0] - v[j];
            if (cur < minv[j]) minv[j] = cur, way[j] = j0;
            if (minv[j] < delta) delta = minv[j], j1 = j;
          }
        for (int j = 0; j < (m + 1); j++) {
          if (used[j]) u[p[j]] += delta, v[j] -= delta;
          else minv[j] -= delta;
        }
        j0 = j1;
      } while (p[j0] != 0);
      do {
        int j1 = way[j0];
        p[j0] = p[j1];
        j0 = j1;
      } while (j0);
    }
    for (int j = 1; j < (m + 1); j++) l_to_r[p[j]] = j;
    min_weight = -v[0];
  }
};
