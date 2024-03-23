/**
 * @code{.cpp}
       vector<int64_t> a;
       vector<int> le = mono_st(a, less()); // greater(), less_equal(), greater_equal()
 * @endcode
 * @param a array
 * @param cmp transitive compare operator
 * @returns vector le where le[i] = max index such that: le[i] < i and
 *          cmp(a[le[i]], a[i]). If no index exists, le[i] = -1
 * @time O(n)
 * @space a O(n) vector is allocated and returned
 */
template <class T, class F> vector<int> mono_st(const vector<T>& a, F cmp) {
  vector<int> le(ssize(a));
  for (int i = 0; i < ssize(a); i++)
    for (le[i] = i - 1; le[i] >= 0 && !cmp(a[le[i]], a[i]);) le[i] = le[le[i]];
  return le;
}
/**
 * @code{.cpp}
       vector<int64_t> a;
       auto le = mono_st(a, less()), ri = mono_range(le); // greater(), less_equal(), greater_equal()
 * @endcode
 * @param le monotonic stack array of a
 * @returns vector ri where ri[i] = min index such that: i < ri[i] and
 *          !cmp(a[i], a[ri[i]]). If no index exists, ri[i] = n
 * @time O(n)
 * @space a O(n) vector is allocated and returned
 */
vector<int> mono_range(const vector<int>& le) {
  vector<int> ri(ssize(le), ssize(le));
  for (int i = 0; i < ssize(le); i++)
    for (int j = i - 1; j != le[i]; j = le[j]) ri[j] = i;
  return ri;
}
/**
 * @param grid an n-by-m boolean array
 * @returns an (n+1)-by-(m+1) array cnt where cnt[i][j] = the number of times
 * an i-by-j sub rectangle appears in the matrix such that all i*j cells in the
 * sub rectangle are 1. cnt[i][0] and cnt[0][j] will contain garbage values.
 * @time O(n * m)
 * @space this function allocates/returns a O(n * m) vector
 */
vector<vector<int>> count_rectangles(const vector<vector<bool>>& grid) {
  int n = ssize(grid), m = ssize(grid[0]);
  vector cnt(n + 1, vector(m + 1, 0));
  vector<int> h(m);
  for (const auto& row : grid) {
    transform(begin(h), end(h), begin(row), begin(h), [](int a, bool g) {
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
