//! returns the number of distinct subsequences
//!   of a, including the empty subsequence
//! @time O(n log n)
//! @space O(n)
int num_subsequences(const vector<int>& a, int mod) {
  vector dp(ssize(a) + 1, 1);
  map<int, int> last;
  for (int i = 0; i < ssize(a); i++) {
    int& cur = dp[i + 1] = 2 * dp[i];
    if (cur >= mod) cur -= mod;
    auto [it, ins] = last.emplace(a[i], i);
    if (!ins) {
      cur -= dp[exchange(it->second, i)];
      if (cur < 0) cur += mod;
    }
  }
  return dp.back();
}
