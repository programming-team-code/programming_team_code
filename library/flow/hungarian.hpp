//! @file
#pragma once
//! @see https://e-maxx.ru/algo/assignment_hungary
//! @code{.cpp}
//!     auto [min_weight, l_to_r] = hungarian(cost);
//! @endcode
//! Calculates a matching: number of edges is maximized, but since it's a
//! complete bipartite graph with n <= m, this matching always has size n. Of
//! all ways to do this, sum of edge weights is minimized.
struct hungarian {
  ll min_weight;  //!< sum of edge weights in matching
  vi l_to_r;  //!< edge v <=> l_to_r[v] is in the matching, 1<=v<=n; 1<=l_to_r[v]<=m
  //! @param cost (n+1)-by-(m+1) array: cost[u][v] = weight (can be negative) of
  //! the edge u <=> v, 1<=u<=n; 1<=v<=m, n<=m
  //! @time O(n^2 * m)
  //! @space besides the O(n * m) `cost` param, this allocates `l_to_r`
  //! which is O(n), and various O(m) arrays are also allocated temporarily
  hungarian(const vector<vector<ll>>& cost) : l_to_r(sz(cost)) {
    int n = sz(cost), m = sz(cost[0]);
    vi p(m), way(m);
    vector<ll> u(n), v(m);
    rep(i, 1, n) {
      p[0] = i;
      int j0 = 0;
      vector minv(m, LLONG_MAX);
      vector<bool> used(m);
      do {
        used[j0] = 1;
        int i0 = p[j0], j1 = 0;
        ll delta = LLONG_MAX;
        rep(j, 1, m) if (!used[j]) {
          ll cur = cost[i0][j] - u[i0] - v[j];
          if (cur < minv[j]) minv[j] = cur, way[j] = j0;
          if (minv[j] < delta) delta = minv[j], j1 = j;
        }
        rep(j, 0, m) {
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
    rep(j, 1, m) l_to_r[p[j]] = j;
    min_weight = -v[0];
  }
};
