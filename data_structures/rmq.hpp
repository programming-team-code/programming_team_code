//! @code
//!   RMQ rmq1(a, ranges::min); // -std=c++20
//!   RMQ rmq2(a, [&](auto& x, auto& y) {
//!     return min(x, y);
//!   });
//!   vector<RMQ<int, function<int(int, int)>>>
//!     rmqs(3, {{}, NULL});
//!   rmqs[1] = {a, ranges::min};
//! @endcode
//! @time O(nlogn + q)
//! @space O(nlogn)
template<class T, class F> struct RMQ {
  vector<vector<T>> dp;
  F op;
  RMQ(const vector<T>& a, F a_op): dp(1, a), op(a_op) {
    for (int i = 0; (2 << i) <= ssize(a); i++) {
      dp.emplace_back(ssize(a) - (2 << i) + 1);
      transform(begin(dp[i]), end(dp[i]) - (1 << i),
        begin(dp[i]) + (1 << i), begin(dp[i + 1]), op);
    }
  }
  T query(int l, int r) { // [l, r)
    assert(l < r);
    int lg = __lg(r - l);
    return op(dp[lg][l], dp[lg][r - (1 << lg)]);
  }
};
