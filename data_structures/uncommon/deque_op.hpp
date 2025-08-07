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
    rebuild(a, ssize(a) / 2);
  }
  T query() {
    if (empty(l)) return r.back()[1];
    if (empty(r)) return l.back()[1];
    return op(l.back()[1], r.back()[1]);
  }
  T operator[](int i) {
    return (i < ssize(l) ? l[ssize(l) - i - 1]
                         : r[i - ssize(l)])[0];
  }
  T front() { return (empty(l) ? r[0] : l.back())[0]; }
  T back() { return (empty(r) ? l[0] : r.back())[0]; }
  int siz() { return ssize(l) + ssize(r); }
  void push_back(T elem) {
    r.push_back(
      {elem, empty(r) ? elem : op(r.back()[1], elem)});
  }
  void pop_back() {
    if (empty(r)) {
      vector<T> a(ssize(l));
      transform(begin(l), end(l), rbegin(a),
        [](dt& x) { return x[0]; });
      rebuild(a, ssize(a) / 2);
    }
    r.pop_back();
  }
  void push_front(T elem) {
    l.push_back(
      {elem, empty(l) ? elem : op(elem, l.back()[1])});
  }
  void pop_front() {
    if (empty(l)) {
      vector<T> a(ssize(r));
      transform(begin(r), end(r), begin(a),
        [](dt& x) { return x[0]; });
      rebuild(a, (ssize(a) + 1) / 2);
    }
    l.pop_back();
  }
  void rebuild(const vector<T>& a, int sz_le) {
    vector<T> presum(ssize(a));
    partial_sum(rend(a) - sz_le, rend(a),
      rend(presum) - sz_le,
      [&](T x, T y) { return op(y, x); });
    partial_sum(sz_le + begin(a), end(a),
      begin(presum) + sz_le, op);
    l.resize(sz_le);
    r.resize(ssize(a) - sz_le);
    transform(begin(a), begin(a) + sz_le, begin(presum),
      rbegin(l), [](T x, T y) { return dt{x, y}; });
    transform(sz_le + begin(a), end(a),
      begin(presum) + sz_le, begin(r),
      [](T x, T y) { return dt{x, y}; });
  }
};
