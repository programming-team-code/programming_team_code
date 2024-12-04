#pragma once
//! @code
//!   rmq_inc rmq3(a, ranges::min);
//!   rmq_inc rmq4(a, [&](auto& x, auto& y) {
//!     return min(x, y);
//!   });
//!   vector<rmq_inc<int, function<int(int, int)>>>
//!     rmqs2(3, {{}, NULL});
//!   rmqs2[1] = {a, ranges::min};
//! @endcode
//! @time O(nlogn + q)
//! @space O(nlogn)
template<class T, auto OP> struct rmq_inc {
  vector<vector<T>> dp;
  rmq_inc(const vector<T>& a): dp(1, a) {
    for (int i = 0; (2 << i) <= sz(a); i++) {
      dp.emplace_back(sz(a) - (2 << i) + 1);
      ranges::transform(dp[i], dp[i] | views::drop(1 << i),
        begin(dp[i + 1]), OP);
    }
  }
  T query(int l, int r) { // [l, r]
    assert(l <= r);
    int lg = __lg(r - l + 1);
    return OP(dp[lg][l], dp[lg][r - (1 << lg) + 1]);
  }
};
