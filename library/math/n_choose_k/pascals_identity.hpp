#pragma once
constexpr int mod = 17; //!< composite ok
vector<vector<ll>> ch(1010); //!< ch[n][k] = n choose k
rep(i, 0, sz(ch)) {
  ch[i].resize(i + 1, 1);
  rep(j, 1, i) ch[i][j] =
    (ch[i - 1][j] + ch[i - 1][j - 1]) % mod;
}
