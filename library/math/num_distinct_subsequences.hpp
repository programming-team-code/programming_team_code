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
    auto [it, ins] = last.emplace(a[i], i);
    if (!ins) {
      cur -= dp[exchange(it->second, i)];
      if (cur < 0) cur += mod;
    }
  }
  return dp.back();
}
