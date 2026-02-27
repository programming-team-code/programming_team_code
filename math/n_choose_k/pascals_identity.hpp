const int mod = 17; //!< composite ok
vector<vector<int64_t>> ch(
  1010); //!< ch[n][k] = n choose k
for (int i = 0; i < ssize(ch); i++) {
  ch[i].resize(i + 1, 1);
  for (int j = 1; j < i; j++)
    ch[i][j] = (ch[i - 1][j] + ch[i - 1][j - 1]) % mod;
}
