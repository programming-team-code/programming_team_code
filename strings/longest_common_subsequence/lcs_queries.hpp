//! @time O(n + q log n)
//! @space O(n)
struct BIT {
  vector<int64_t> s;
  BIT(int n): s(n) {}
  BIT(const vector<int64_t>& a): s(a) {
    for (int i = 0; i < ssize(a); i++) {
      int j = i | (i + 1);
      if (j < ssize(a)) s[j] += s[i];
    }
  }
  void update(int i, int64_t d) {
    for (; i < ssize(s); i |= i + 1) s[i] += d;
  }
  int64_t query(int r) {
    int64_t ret = 0;
    for (; r > 0; r &= r - 1) ret += s[r - 1];
    return ret;
  }
  int64_t query(int l, int r) {
    return query(r) - query(l);
  }
  //! Requires sum of [i,i] >= 0
  //! Returns min r s.t. sum of [0,r] >= sum
  //! Returns n if sum of [0,n-1] < sum
  int walk(int64_t sum) {
    if (sum <= 0) return -1;
    int r = 0;
    for (int i = bit_floor(size(s)); i; i /= 2)
      if (r + i <= ssize(s) && s[r + i - 1] < sum)
        sum -= s[(r += i) - 1];
    return r;
  }
};
//! https://codeforces.com/blog/entry/111625
//! Given strings s, t (s initially empty):
//!  -append character onto s
//!  -given range [l,r):
//!     size(LCS(s,t.substr(l,r-l))) = number
//!       of indexes i in [l,r) with dp[i] < l
//! @time O(|s| * |t|)
//! @space O(|t|)
template<class T> struct lcs_dp {
  T t;
  vector<int> dp;
  lcs_dp(const T& t): t(t), dp(ssize(t)) {
    iota(begin(dp), end(dp), 0);
  }
  void push_onto_s(int c) {
    int v = -1;
    for (int i = 0; i < ssize(t); i++)
      if (c == t[i] || dp[i] < v) swap(dp[i], v);
  }
};
//! @code
//!   string s,t;
//!   vi lcs_len = lcs_queries(s, t, queries);
//!   vi s_vec,t_vec;
//!   vi lcs_len1 = lcs_queries(s_vec, t_vec, queries);
//! @endcode
//! lcs_len[i] = size(LCS(
//!   s[0,queries[i][0]),
//!   t[queries[i][1],queries[i][2])
//! ))
//! @time O(n*m*log(m) + q*log(m) + q*log(q))
//! @space O(n + m + q)
vector<int> lcs_queries(const auto& s, const auto& t,
  const vector<array<int, 3>>& queries) {
  int n = ssize(s), m = ssize(t), q = ssize(queries);
  vector<vector<array<int, 3>>> qs(n);
  for (int i = 0; i < q; i++) {
    auto [s_r, t_le, t_ri] = queries[i];
    if (s_r == 0 || t_le == m) continue;
    qs[s_r - 1].push_back({t_le, t_ri, i});
  }
  lcs_dp lcs(t);
  vector<int> res(q);
  for (int i = 0; i < n; i++) {
    lcs.push_onto_s(s[i]);
    BIT bit(m);
    vector<int> dp_inv(m, -1);
    for (int j = 0; j < m; j++)
      if (lcs.dp[j] == -1) bit.update(j, 1);
      else dp_inv[lcs.dp[j]] = j;
    ranges::sort(qs[i]);
    int j = 0;
    for (int t_le = 0; t_le < m; t_le++) {
      while (j < ssize(qs[i]) && qs[i][j][0] == t_le)
        res[qs[i][j][2]] = bit.query(t_le, qs[i][j][1]),
        j++;
      if (dp_inv[t_le] != -1) bit.update(dp_inv[t_le], 1);
    }
  }
  return res;
}
