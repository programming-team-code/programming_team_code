//! @file
#pragma once
//! @see https://codeforces.com/blog/entry/87940
//! Disjoint RMQ is like normal RMQ except the 2 query ranges never overlap.
//! @code{.cpp}
//!     //usage for min and # of mins:
//!     vector<pair<ll, int>> a; //initialize a[i].second = 1
//!     disjoint_rmq rmq(a, [&](auto& x, auto& y) {
//!         if (x.first == y.first) return make_pair(x.first, x.second + y.second);
//!         return min(x, y);
//!     });
//! @endcode
template<class T, class F> struct disjoint_rmq {
  vector<vector<T>> dp;
  //! examples:
  //! - min and # of mins.
  //! - product under composite mod
  //! - matrix multiply
  //! - function composition
  F op;
  //! @param a static array
  //! @param a_op any associative operation
  //! @time O(n log n)
  //! @space O(n log n) for `dp` vector
  disjoint_rmq(const vector<T>& a, F a_op): op(a_op) {
    for (int len = 1, n = sz(a); len <= n; len *= 2) {
      dp.emplace_back(n);
      for (int le = 0; le < n; le += 2 * len) {
        int mi = min(n, le + len), ri = min(n, le + 2 * len);
        partial_sum(rend(a) - mi, rend(a) - le,
          rend(dp.back()) - mi,
          [&](T x, T y) { return op(y, x); });
        partial_sum(begin(a) + mi, begin(a) + ri,
          begin(dp.back()) + mi, op);
      }
    }
  }
  //! @param le,ri defines range [le, ri)
  //! @returns a[le] op a[le + 1] op ... op a[ri - 1]
  //! @time O(1)
  //! @space O(1)
  T query(int le, int ri) {
    assert(le < ri);
    if (ri - le == 1) return dp[0][le];
    int lg = __lg(le ^ (ri - 1));
    return op(dp[lg][le], dp[lg][ri - 1]);
  }
};
