#pragma once
//! https://github.com/suisen-cp/cp-library-cpp/blob/main/library/datastructure/deque_aggregation.hpp
//! @code
//!   deq dq(a, ranges::min);
//! @endcode
//! @time operations are O(1) ammortized
//! @space O(n)
template<class T, class F> struct deq {
  using dt = array<T, 2>;
  F op;
  vector<dt> l, r;
  deq(const vector<T>& a, F op): op(op) {
    rebuild(a, sz(a) / 2);
  }
  T query() {
    if (empty(l)) return r.back()[1];
    if (empty(r)) return l.back()[1];
    return op(l.back()[1], r.back()[1]);
  }
  int siz() { return sz(l) + sz(r); }
  void push_back(T elem) {
    r.push_back(
      {elem, empty(r) ? elem : op(r.back()[1], elem)});
  }
  void pop_front() {
    if (empty(l)) {
      vector<T> a(sz(r));
      transform(all(r), begin(a),
        [](dt& x) { return x[0]; });
      rebuild(a, (sz(a) + 1) / 2);
    }
    l.pop_back();
  }
  void rebuild(const vector<T>& a, int sz_le) {
    vector<T> presum(sz(a));
    partial_sum(rend(a) - sz_le, rend(a),
      rend(presum) - sz_le,
      [&](T x, T y) { return op(y, x); });
    partial_sum(sz_le + all(a), begin(presum) + sz_le, op);
    l.resize(sz_le);
    r.resize(sz(a) - sz_le);
    transform(begin(a), begin(a) + sz_le, begin(presum),
      rbegin(l), [](T x, T y) { return dt{x, y}; });
    transform(sz_le + all(a), begin(presum) + sz_le,
      begin(r), [](T x, T y) { return dt{x, y}; });
  }
#include "deque.hpp"
#include "index.hpp"
#include "front.hpp"
#include "back.hpp"
};
