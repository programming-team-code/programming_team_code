#pragma once
//! returns the number of distinct subsequences
//!   of a, including the empty subsquence
//! @time O(n log n)
//! @space O(n)
int num_subsequences(const vi& a, int mod) {
  vector dp(sz(a) + 1, 1);
  map<int, int> last;
  rep(i, 0, sz(a)) {
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
