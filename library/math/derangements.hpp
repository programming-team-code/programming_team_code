#pragma once
//! https://oeis.org/A000166
//! @code
//!   auto der = derangements(n, mod);
//! @endcode
//! der[i] = number of permutations p with p[i]!=i
//! @time O(n)
//! @space O(n)
vector<ll> derangements(int n, int mod) {
  vector<ll> dp(n);
  dp[0] = 1;
  rep(i, 2, n) dp[i] =
    (i - 1) * (dp[i - 1] + dp[i - 2]) % mod;
  return dp;
}
