/** @file */
#pragma once
const int mx = 1010 /**< mx > mod is ok */, mod = 17; /**< must be prime */
vector<vector<ll>> choose(mx); /**< choose[n][k] = n choose k */
rep(i, 0, mx) {
  choose[i].resize(i + 2);
  choose[i][0] = 1;
  rep(j, 1, i + 1)
      choose[i][j] = (choose[i - 1][j] + choose[i - 1][j - 1]) % mod;
}
