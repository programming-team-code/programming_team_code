//! @code
//!   auto mono_le1 = mono_st(a, less());
//!   // less_equal(), greater(), greater_equal()
//! @endcode
//! when cmp == less():
//!   a[mono_le1[i]] < a[i]
//! @time O(n)
//! @space O(n)
template<class T, class F>
vector<int> mono_st(const vector<T>& a, F cmp) {
  vector<int> le((int)size(a));
  for (int i = 0; i < ((int)size(a)); i++)
    for (le[i] = i - 1;
         le[i] >= 0 && !cmp(a[le[i]], a[i]);)
      le[i] = le[le[i]];
  return le;
}
//! @code
//!   auto mono_le2 = mono_st(a, less());
//!   auto mono_ri2 = mono_range(mono_le2);
//!   // less_equal(), greater(), greater_equal()
//! @endcode
//! when cmp == less():
//!   a[mono_le2[i]] < a[i] >= a[mono_ri2[i]]
//! @time O(n)
//! @space O(n)
vector<int> mono_range(const vector<int>& le) {
  vector<int> ri((int)size(le), (int)size(le));
  for (int i = 0; i < ((int)size(le)); i++)
    for (int j = i - 1; j != le[i]; j = le[j]) ri[j] = i;
  return ri;
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
  int n = (int)size(grid), m = (int)size(grid[0]);
  vector cnt(n + 1, vector(m + 1, 0));
  vector<int> h(m);
  for (const auto& row : grid) {
    transform(begin(h), end(h), begin(row), begin(h),
      [](int a, bool g) { return g * (a + 1); });
    vector<int> le(mono_st(h, less())), ri(mono_range(le));
    for (int j = 0; j < (m); j++) {
      int cnt_l = j - le[j] - 1, cnt_r = ri[j] - j - 1;
      cnt[h[j]][cnt_l + cnt_r + 1]++;
      cnt[h[j]][cnt_l]--;
      cnt[h[j]][cnt_r]--;
    }
  }
  for (int i = 1; i < (n + 1); i++)
    for (int k = 0; k < (2); k++)
      for (int j = m; j > 1; j--)
        cnt[i][j - 1] += cnt[i][j];
  for (int i = n; i > 1; i--)
    for (int j = 1; j < (m + 1); j++)
      cnt[i - 1][j] += cnt[i][j];
  return cnt;
}
