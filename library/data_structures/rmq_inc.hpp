#pragma once
//! @code
//!   rmq_inc rmq1(a, ranges::min);
//!   rmq_inc rmq2(a, [&](auto& x, auto& y) {
//!     return min(x, y);
//!   });
//!   vector<rmq_inc<int, function<int(int, int)>>>
//!     rmqs(3, {{}, NULL});
//!   rmqs[1] = {a, ranges::min};
//! @endcode
//! @time O(nlogn + q)
//! @space O(nlogn)
template<class T, class F> struct rmq_inc {
  vector<vector<T>> dp;
  F op;
  rmq_inc(const vector<T>& a, F op): dp(1, a), op(op) {
    for (int i = 0; (2 << i) <= sz(a); i++) {
      dp.emplace_back(sz(a) - (2 << i) + 1);
      ranges::transform(dp[i], dp[i] | views::drop(1 << i),
        begin(dp[i + 1]), op);
    }
  }
  T query(int l, int r) { // [l, r]
    assert(l <= r);
    int lg = __lg(r - l + 1);
    return op(dp[lg][l], dp[lg][r - (1 << lg) + 1]);
  }
};
