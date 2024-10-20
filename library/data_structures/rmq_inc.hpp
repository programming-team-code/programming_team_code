#pragma once
//! @code
//!   rmq_inc rmq3(a, ranges::min); // -std=c++20
//!   rmq_inc rmq4(a, [&](auto& x, auto& y) {
//!     return min(x, y);
//!   });
//!   vector<rmq_inc<int, function<int(int, int)>>>
//!     rmqs2(3, {{}, NULL});
//!   rmqs2[1] = {a, ranges::min};
//! @endcode
//! @time O(nlogn + q)
//! @space O(nlogn)
template<class T, class F> struct rmq_inc {
  vector<vector<T>> dp;
  F op;
  rmq_inc(const vector<T>& a, F a_op): dp(1, a), op(a_op) {
    for (int i = 0; (2 << i) <= sz(a); i++) {
      dp.emplace_back(sz(a) - (2 << i) + 1);
      transform(all(dp[i]) - (1 << i),
        begin(dp[i]) + (1 << i), begin(dp[i + 1]), op);
    }
  }
  T query(int l, int r) { // [l, r]
    assert(l <= r);
    int lg = __lg(r - l + 1);
    return op(dp[lg][l], dp[lg][r - (1 << lg) + 1]);
  }
};
