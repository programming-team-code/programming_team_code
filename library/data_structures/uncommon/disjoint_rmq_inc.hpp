#pragma once
//! https://codeforces.com/blog/entry/87940
//! Disjoint RMQ is like normal RMQ except
//!   the 2 query ranges never overlap.
//! @code
//!   disjoint_rmq dis_rmq2(a, [&](int x, int y) {
//!     return 1LL*x*y%10;
//!   });
//! @endcode
//! @time O(nlogn + q)
//! @space O(nlogn)
template<class T, class F> struct disjoint_rmq_inc {
  vector<vector<T>> dp;
  F op;
  disjoint_rmq_inc(const vector<T>& a, F a_op): op(a_op) {
    for (int len = 1, n = sz(a); len <= n; len *= 2) {
      dp.emplace_back(n);
      for (int le = 0; le < n; le += 2 * len) {
        int mi = min(n, le + len),
            ri = min(n, le + 2 * len);
        partial_sum(rend(a) - mi, rend(a) - le,
          rend(dp.back()) - mi,
          [&](T x, T y) { return op(y, x); });
        partial_sum(begin(a) + mi, begin(a) + ri,
          begin(dp.back()) + mi, op);
      }
    }
  }
  T query(int le, int ri) { // [le, ri]
    if (le == ri) return dp[0][le];
    int lg = __lg(le ^ ri);
    return op(dp[lg][le], dp[lg][ri]);
  }
};
