//! @code
//!   vi le = mono_st(a, less());
//!   // less_equal(), greater(), greater_equal()
//! @endcode
//! when cmp == less():
//!   a[le[i]] < a[i]
//! @time O(n)
//! @space O(n)
vector<int> mono_st(const auto& a, const auto& cmp) {
  vector<int> l(ssize(a));
  for (int i = 0; i < ssize(a); i++)
    for (l[i] = i - 1; l[i] >= 0 && !cmp(a[l[i]], a[i]);)
      l[i] = l[l[i]];
  return l;
}
//! @code
//!   vi le = mono_st(a, less()), ri = mono_range(le);
//!   // less_equal(), greater(), greater_equal()
//! @endcode
//! when cmp == less():
//!   a[le[i]] < a[i] >= a[ri[i]]
//! @time O(n)
//! @space O(n)
vector<int> mono_range(const vector<int>& l) {
  vector<int> r(ssize(l), ssize(l));
  for (int i = 0; i < ssize(l); i++)
    for (int j = i - 1; j != l[i]; j = l[j]) r[j] = i;
  return r;
}
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
vector<vector<int>> count_rectangles(
  const vector<vector<bool>>& grid) {
  int n = ssize(grid), m = ssize(grid[0]);
  vector cnt(n + 1, vector(m + 1, 0));
  vector<int> h(m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++)
      h[j] = grid[i][j] * (h[j] + 1);
    vector<int> l(mono_st(h, less())), r(mono_range(l));
    for (int j = 0; j < m; j++) {
      int cnt_l = j - l[j] - 1, cnt_r = r[j] - j - 1;
      cnt[h[j]][cnt_l + cnt_r + 1]++;
      cnt[h[j]][cnt_l]--;
      cnt[h[j]][cnt_r]--;
    }
  }
  for (int i = 1; i < n + 1; i++)
    for (int k = 0; k < 2; k++)
      for (int j = m; j > 1; j--)
        cnt[i][j - 1] += cnt[i][j];
  for (int i = n; i > 1; i--)
    for (int j = 1; j < m + 1; j++)
      cnt[i - 1][j] += cnt[i][j];
  return cnt;
}
