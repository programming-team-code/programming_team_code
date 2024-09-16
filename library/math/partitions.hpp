//! @file
#pragma once
const int mod = 998'244'353;
//! @see https://oeis.org/A000041
//! @param n an integer
//! @returns array p where p[i] = number of partitions of i
//! numbers
//! @time O(n sqrt n) note there does exist a O(n log n)
//! solution as well
//! @space O(n) for `dp` vector
vector<ll> partitions(int n) {
  vector<ll> dp(n, 1);
  rep(i, 1, n) {
    ll sum = 0;
    for (int j = 1, pent = 1, sign = 1; pent <= i;
         j++, pent += 3 * j - 2, sign = -sign) {
      if (pent + j <= i)
        sum += dp[i - pent - j] * sign + mod;
      sum += dp[i - pent] * sign + mod;
    }
    dp[i] = sum % mod;
  }
  return dp;
}
