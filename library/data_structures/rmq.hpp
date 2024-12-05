#pragma once
//! @code
//!   RMQ rmq1(a, ranges::min);
//!   RMQ rmq2(a, [&](auto& x, auto& y) {
//!     return min(x, y);
//!   });
//!   vector<RMQ<int, function<int(int, int)>>>
//!     rmqs(3, {{}, NULL});
//!   rmqs[1] = {a, ranges::min};
//! @endcode
//! @time O(nlogn + q)
//! @space O(nlogn)
// NOLINTNEXTLINE(readability-identifier-naming)
template<class T, class F> struct RMQ {
  vector<vector<T>> dp;
  F op;
  RMQ(const vector<T>& a, F op): dp(1, a), op(op) {
    for (int i = 0; (2 << i) <= sz(a); i++) {
      dp.emplace_back(sz(a) - (2 << i) + 1);
      ranges::transform(dp[i], dp[i] | views::drop(1 << i),
        begin(dp[i + 1]), op);
    }
  }
  T query(int l, int r) { // [l, r)
    assert(l < r);
    int l = __lg(r - l);
    return op(dp[lg][l], dp[lg][r - (1 << lg)]);
  }
};
