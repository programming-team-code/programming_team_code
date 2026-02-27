const int mod = 998'244'353;
//! https://oeis.org/A000041
//! @code
//!   auto p = partitions(n);
//! @endcode
//! p[i] = number of partitions of i numbers
//! @time O(n sqrt n)
//! @space O(n)
vector<int64_t> partitions(int n) {
  vector<int64_t> dp(n, 1);
  for (int i = 1; i < n; i++) {
    int64_t sum = 0;
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
