#pragma once
//! @code
//!   rmq_inc rmq1(a, ranges::min); // -std=c++20
//!   rmq_inc rmq2(a, [&](auto& x, auto& y) {
//!     return min(x, y);
//!   });
//! @endcode
//! @time O(nlogn + q)
//! @space O(nlogn)
template <class T, class F> struct rmq_inc {
  vector<vector<T>> dp;
  F op;
  rmq_inc(const vector<T>& a, F a_op) : dp(1, a), op(a_op) {
    for (int i = 0; (2 << i) <= sz(a); i++) {
      dp.emplace_back(sz(a) - (2 << i) + 1);
      transform(all(dp[i]) - (1 << i),
                begin(dp[i]) + (1 << i), begin(dp[i + 1]), op);
    }
  }
  T query(int le, int ri) {  // [le, ri]
    assert(le <= ri);
    int lg = __lg(ri - le + 1);
    return op(dp[lg][le], dp[lg][ri - (1 << lg) + 1]);
  }
};