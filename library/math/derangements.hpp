/** @file */
#pragma once
/**
 * @see https://oeis.org/A000166
 * @param n size
 * @param mod an integer
 * @return number of permutations p such that p[i] != i
 * @time O(n)
 * @space O(n) for `dp` vector
 */
vector<ll> derangements(int n, int mod) {
  vector<ll> dp(n);
  dp[0] = 1;
  rep(i, 2, n)
      dp[i] = (i - 1) * (dp[i - 1] + dp[i - 2]) % mod;
  return dp;
}
