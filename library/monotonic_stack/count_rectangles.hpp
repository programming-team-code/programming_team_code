#pragma once
#include "monotonic_range.hpp"
//! @code
//!   auto cnt = count_rectangles(grid);
//! @endcode
//!
//! cnt[i][j] = the number of times an i-by-j
//!   sub rectangle appears in the matrix such that
//!   all i*j cells in the sub rectangle are 1
//!
//! cnt[i][0] and cnt[0][j] will contain garbage numbers.
//! @time O(n * m)
//! @space O(n * m)
vector<vi> count_rectangles(
    const vector<vector<bool>>& grid) {
  int n = sz(grid), m = sz(grid[0]);
  vector cnt(n + 1, vector(m + 1, 0));
  vi h(m);
  for (const auto& row : grid) {
    transform(all(h), begin(row), begin(h),
              [](int a, bool g) { return g * (a + 1); });
    vi le(mono_st(h, less())), ri(mono_range(le));
    rep(j, 0, m) {
      int cnt_l = j - le[j] - 1, cnt_r = ri[j] - j - 1;
      cnt[h[j]][cnt_l + cnt_r + 1]++;
      cnt[h[j]][cnt_l]--;
      cnt[h[j]][cnt_r]--;
    }
  }
  rep(i, 1, n + 1) rep(k, 0, 2) for (int j = m; j > 1; j--)
      cnt[i][j - 1] += cnt[i][j];
  for (int i = n; i > 1; i--)
    rep(j, 1, m + 1) cnt[i - 1][j] += cnt[i][j];
  return cnt;
}
