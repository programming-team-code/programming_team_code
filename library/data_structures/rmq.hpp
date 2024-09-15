//! @file
#pragma once
/**
 * @code{.cpp}
       vector<ll> a;
       RMQ rmq(a, ranges::min); // -std=c++20
       RMQ rmq(a, [&](auto& x, auto& y) { return min(x, y); });
 * @endcode
 */
// NOLINTNEXTLINE(readability-identifier-naming)
template <class T, class F> struct RMQ {
  vector<vector<T>> dp;
  F op;
  /**
   * @param a static array
   * @param a_op any associative, commutative, idempotent operation
   * @time O(n log n)
   * @space O(n log n) for `dp` vector
   */
  RMQ(const vector<T>& a, F a_op) : dp(1, a), op(a_op) {
    for (int i = 0; (2 << i) <= sz(a); i++) {
      dp.emplace_back(sz(a) - (2 << i) + 1);
      transform(all(dp[i]) - (1 << i), begin(dp[i]) + (1 << i), begin(dp[i + 1]), op);
    }
  }
  /**
   * @param le,ri defines range [le, ri)
   * @returns a[le] op a[le + 1] op ... op a[ri - 1]
   * @time O(1)
   * @space O(1)
   */
  T query(int le, int ri) {
    assert(le < ri);
    int lg = __lg(ri - le);
    return op(dp[lg][le], dp[lg][ri - (1 << lg)]);
  }
};
