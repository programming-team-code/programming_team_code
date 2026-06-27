//! returns the number of distinct subsequences
//!   of a, including the empty subsquence
//! @time O(n log n)
//! @space O(n)
int num_subsequences(const vector<int>& a, int mod) {
  vector dp(ssize(a) + 1, 1);
  map<int, int> last;
  for (int i = 0; i < ssize(a); i++) {
    int& curr = dp[i + 1] = 2 * dp[i];
    if (curr >= mod) curr -= mod;
    auto it = last.find(a[i]);
    if (it != end(last)) {
      curr -= dp[it->second];
      if (curr < 0) curr += mod;
      it->second = i;
    } else last[a[i]] = i;
  }
  return dp.back();
}
