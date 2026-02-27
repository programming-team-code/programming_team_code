//! https://oeis.org/A000166
//! @code
//!   auto der = derangements(n, mod);
//! @endcode
//! der[i] = number of permutations p with p[i]!=i
//! @time O(n)
//! @space O(n)
vector<int64_t> derangements(int n, int mod) {
  vector<int64_t> dp(n);
  dp[0] = 1;
  for (int i = 2; i < n; i++)
    dp[i] = (i - 1) * (dp[i - 1] + dp[i - 2]) % mod;
  return dp;
}
