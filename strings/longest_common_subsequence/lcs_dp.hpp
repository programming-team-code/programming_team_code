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
