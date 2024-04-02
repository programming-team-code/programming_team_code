/** @file */
#pragma once
#include "monotonic_range.hpp"
/**
 * @param grid an n-by-m boolean array
 * @returns an (n+1)-by-(m+1) array cnt where cnt[i][j] = the number of times
 * an i-by-j sub rectangle appears in the matrix such that all i*j cells in the
 * sub rectangle are 1. cnt[i][0] and cnt[0][j] will contain garbage values.
 * @time O(n * m)
 * @space this function allocates/returns a O(n * m) vector
 */
vector<vi> count_rectangles(const vector<vector<bool>>& grid) {
  int n = sz(grid), m = sz(grid[0]);
  vector cnt(n + 1, vector(m + 1, 0));
  vi h(m);
  for (const auto& row : grid) {
    transform(all(h), begin(row), begin(h), [](int a, bool g) {
      return g * (a + 1);
    });
    auto le(mono_st(h, less())), ri(mono_range(le));
    for (int j = 0; j < m; j++) {
      int cnt_l = j - le[j] - 1, cnt_r = ri[j] - j - 1;
      cnt[h[j]][cnt_l + cnt_r + 1]++;
      cnt[h[j]][cnt_l]--;
      cnt[h[j]][cnt_r]--;
    }
  }
  for (int i = 1; i <= n; i++)
    for (int k = 0; k < 2; k++)
      for (int j = m; j > 1; j--)
        cnt[i][j - 1] += cnt[i][j];
  for (int i = n; i > 1; i--)
    for (int j = 1; j <= m; j++)
      cnt[i - 1][j] += cnt[i][j];
  return cnt;
}
