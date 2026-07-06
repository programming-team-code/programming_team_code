#pragma once
//! returns the number of distinct subsequences
//!   of a, including the empty subsquence
//! @time O(n log n)
//! @space O(n)
int num_subsequences(const vi& a, int mod) {
  vector dp(sz(a) + 1, 1);
  map<int, int> last;
  rep(i, 0, sz(a)) {
    int& cur = dp[i + 1] = 2 * dp[i];
    if (cur >= mod) cur -= mod;
    auto it = last.find(a[i]);
    if (it != end(last)) {
      cur -= dp[it->second];
      if (cur < 0) cur += mod;
      it->second = i;
    } else last[a[i]] = i;
  }
  return dp.back();
}
