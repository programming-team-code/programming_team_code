#pragma once
//! @code
//!   RMQ<int, ranges::min> rmq1(a);
//!   RMQ<int,([&](auto& x, auto& y) {
//!     return x > y ? x : y;
//!   })> rmq2(a);
//!   vector<RMQ<int, function<int(int, int)>>>
//!     rmqs(3, {{}, NULL});
//!   rmqs[1] = {a, ranges::min};
//! @endcode
//! @time O(nlogn + q)
//! @space O(nlogn)
// NOLINTNEXTLINE(readability-identifier-naming)
template<class T, auto OP> struct RMQ {
  vector<vector<T>> dp;
  RMQ(const vector<T>& a): dp(1, a) {
    for (int i = 0; (2 << i) <= sz(a); i++) {
      dp.emplace_back(sz(a) - (2 << i) + 1);
      ranges::transform(dp[i], dp[i] | views::drop(1 << i),
        begin(dp[i + 1]), OP);
    }
  }
  T query(int l, int r) { // [l, r)
    assert(l < r);
    int lg = __lg(r - l);
    return OP(dp[lg][l], dp[lg][r - (1 << lg)]);
  }
};
