//! @file
#pragma once
/**
 * deque with query for operation of the deque
 * @code{.cpp}
       //deque with query for: get min and # of mins in deque
       vector<pair<ll, int>> a; //initialize a[i].second = 1
       deq dq(a, [](auto x, auto y) {
           if (x.first == y.first) return pair(x.first, x.second + y.second);
           return min(x, y);
       });
 * @endcode
 */
template <class T, class F> struct deq {
  using dt = array<T, 2>;
  F op;
  /**
   * @see https://github.com/suisen-cp/cp-library-cpp /blob/main/library/datastructure/deque_aggregation.hpp
   * simulate a deque with 2 stacks:
   * `le`, `ri` are stacks of { number, sum }
   *     accumulate
   *    <-----------  -------> fold numbers from inside
   *   (     le     ][  ri    )
   * @{
   */
  vector<dt> le, ri;
  /** @} */
  /**
   * @param a initial array: a[0] is front, a.back() is back
   * @param a_op associative operation
   * @time O(1)
   * @space O(1)
   */
  deq(const vector<T>& a, F a_op) : op(a_op) { rebuild(a, sz(a) / 2); }
  /**
   * @returns deq[0] op deq[1] op ... op deq.back()
   * @time O(1)
   * @space O(1)
   */
  T query() {
    if (empty(le)) return ri.back()[1];
    if (empty(ri)) return le.back()[1];
    return op(le.back()[1], ri.back()[1]);
  }
  /**
   * @returns size
   * @time O(1)
   * @space O(1)
   */
  int siz() { return sz(le) + sz(ri); }
  /**
   * @param elem element to insert at end
   * @time O(1)
   * @space O(1)
   */
  void push_back(T elem) {
    ri.push_back({elem, empty(ri) ? elem : op(ri.back()[1], elem)});
  }
  /**
   * remove deq[0]
   * @time O(1) ammortized
   * @space O(1) ammortized
   */
  void pop_front() {
    if (empty(le)) {
      vector<T> a(sz(ri));
      transform(all(ri), begin(a), [](dt& x) { return x[0]; });
      rebuild(a, (sz(a) + 1) / 2);
    }
    le.pop_back();
  }
  void rebuild(const vector<T>& a, int sz_le) {
    vector<T> presum(sz(a));
    partial_sum(rend(a) - sz_le, rend(a), rend(presum) - sz_le, [&](T x, T y) { return op(y, x); });
    partial_sum(sz_le + all(a), begin(presum) + sz_le, op);
    le.resize(sz_le);
    ri.resize(sz(a) - sz_le);
    transform(begin(a), begin(a) + sz_le, begin(presum), rbegin(le), [](T x, T y) { return dt{x, y}; });
    transform(sz_le + all(a), begin(presum) + sz_le, begin(ri), [](T x, T y) { return dt{x, y}; });
  }
#include "deque.hpp"
#include "index.hpp"
#include "front.hpp"
#include "back.hpp"
};
