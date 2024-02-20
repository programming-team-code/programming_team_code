/** @file */
#pragma once
const int mx = 1010 /**< mx > mod is ok */, mod = 17; /**< must be prime */
vector<vector<int64_t>> choose(mx); /**< choose[n][k] = n choose k */
for (int i = 0; i < mx; i++) {
	choose[i].resize(i + 2);
	choose[i][0] = 1;
	for (int j = 1; j <= i; j++)
		choose[i][j] = (choose[i - 1][j] + choose[i - 1][j - 1]) % mod;
}
