#pragma once
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
pair<ll, vi> hungarian(const vector<vector<ll>>& cost) {
  int n = sz(cost), m = sz(cost[0]);
  vi p(m), way(m);
  vector<ll> u(n), v(m);
  rep(i, 1, n) {
    p[0] = i;
    int j0 = 0;
    vector minv(m, LLONG_MAX);
    vi used(m);
    do {
      used[j0] = 1;
      int i0 = p[j0], j1 = 0;
      ll delta = LLONG_MAX;
      rep(j, 1, m) if (!used[j]) {
        ll cur = cost[i0][j] - u[i0] - v[j];
        if (cur < minv[j]) minv[j] = cur, way[j] = j0;
        if (minv[j] < delta) delta = minv[j], j1 = j;
      }
      rep(j, 0, m) if (used[j]) u[p[j]] += delta,
        v[j] -= delta;
      else minv[j] -= delta; j0 = j1;
    } while (p[j0] != 0);
    do {
      int j1 = way[j0];
      p[j0] = p[j1];
      j0 = j1;
    } while (j0);
  }
  vi l_to_r(n);
  rep(j, 1, m) l_to_r[p[j]] = j;
  return {-v[0], l_to_r};
}
