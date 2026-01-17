#pragma once
//! https://codeforces.com/blog/entry/87940
//! Disjoint RMQ is like normal RMQ except
//!   the 2 query ranges never overlap.
//! @code
//!   disjoint_rmq rmq(a, [&](int x, int y) {
//!     return 1LL*x*y%10;
//!   });
//! @endcode
//! @time O(nlogn + q)
//! @space O(nlogn)
template<class T, class F> struct disjoint_rmq {
  vector<vector<T>> dp;
  F op;
  disjoint_rmq(const vector<T>& a, F op): op(op) {
    for (int len = 1, n = sz(a); len <= n; len *= 2) {
      dp.emplace_back(n);
      for (int l = 0; l < n; l += 2 * len) {
        int mi = min(n, l + len), r = min(n, l + 2 * len);
        partial_sum(rend(a) - mi, rend(a) - l,
          rend(dp.back()) - mi,
          [&](T x, T y) { return op(y, x); });
        partial_sum(begin(a) + mi, begin(a) + r,
          begin(dp.back()) + mi, op);
      }
    }
  }
  T query(int l, int r) { // [l, r)
    assert(l < r);
    if (r - l == 1) return dp[0][l];
    int lg = __lg(l ^ (r - 1));
    return op(dp[lg][l], dp[lg][r - 1]);
  }
};
