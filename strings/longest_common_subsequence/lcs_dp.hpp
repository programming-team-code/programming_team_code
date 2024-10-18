//! https://codeforces.com/blog/entry/111625
//! Given strings s, t (s initially empty):
//!  -append character onto s
//!  -given range [le,ri):
//!     size(LCS(s,t.substr(le,ri-le))) = number
//!       of indexes i in [le,ri) with dp[i] < le
//! @time O(|s| * |t|)
//! @space O(|t|)
template<class T> struct lcs_dp {
  T t;
  vector<int> dp;
  lcs_dp(const T& a_t): t(a_t), dp((int)size(t)) {
    iota(begin(dp), end(dp), 0);
  }
  void push_onto_s(int c) {
    int v = -1;
    for (int i = 0; i < ((int)size(t)); i++)
      if (c == t[i] || dp[i] < v) swap(dp[i], v);
  }
};
