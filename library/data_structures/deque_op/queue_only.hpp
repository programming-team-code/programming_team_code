#pragma once
//! https://github.com/suisen-cp/cp-library-cpp/blob/main/library/datastructure/deque_aggregation.hpp
//! @code
//!   deq dq(a, [](auto x, auto y) {return min(x, y);});
//! @endcode
//! @time operations are O(1) ammortized
//! @space O(n)
template<class T, class F> struct deq {
  using dt = array<T, 2>;
  F op;
  vector<dt> le, ri;
  deq(const vector<T>& a, F a_op): op(a_op) {
    rebuild(a, sz(a) / 2);
  }
  T query() {
    if (empty(le)) return ri.back()[1];
    if (empty(ri)) return le.back()[1];
    return op(le.back()[1], ri.back()[1]);
  }
  int siz() { return sz(le) + sz(ri); }
  void push_back(T elem) {
    ri.push_back(
      {elem, empty(ri) ? elem : op(ri.back()[1], elem)});
  }
  void pop_front() {
    if (empty(le)) {
      vector<T> a(sz(ri));
      transform(all(ri), begin(a),
        [](dt& x) { return x[0]; });
      rebuild(a, (sz(a) + 1) / 2);
    }
    le.pop_back();
  }
  void rebuild(const vector<T>& a, int sz_le) {
    vector<T> presum(sz(a));
    partial_sum(rend(a) - sz_le, rend(a),
      rend(presum) - sz_le,
      [&](T x, T y) { return op(y, x); });
    partial_sum(sz_le + all(a), begin(presum) + sz_le, op);
    le.resize(sz_le);
    ri.resize(sz(a) - sz_le);
    transform(begin(a), begin(a) + sz_le, begin(presum),
      rbegin(le), [](T x, T y) { return dt{x, y}; });
    transform(sz_le + all(a), begin(presum) + sz_le,
      begin(ri), [](T x, T y) { return dt{x, y}; });
  }
#include "deque.hpp"
#include "index.hpp"
#include "front.hpp"
#include "back.hpp"
};
