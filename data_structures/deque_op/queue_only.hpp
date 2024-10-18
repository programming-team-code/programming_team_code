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
    rebuild(a, (int)size(a) / 2);
  }
  T query() {
    if (empty(le)) return ri.back()[1];
    if (empty(ri)) return le.back()[1];
    return op(le.back()[1], ri.back()[1]);
  }
  int siz() { return (int)size(le) + (int)size(ri); }
  void push_back(T elem) {
    ri.push_back(
      {elem, empty(ri) ? elem : op(ri.back()[1], elem)});
  }
  void pop_front() {
    if (empty(le)) {
      vector<T> a((int)size(ri));
      transform(begin(ri), end(ri), begin(a),
        [](dt& x) { return x[0]; });
      rebuild(a, ((int)size(a) + 1) / 2);
    }
    le.pop_back();
  }
  void rebuild(const vector<T>& a, int sz_le) {
    vector<T> presum((int)size(a));
    partial_sum(rend(a) - sz_le, rend(a),
      rend(presum) - sz_le,
      [&](T x, T y) { return op(y, x); });
    partial_sum(sz_le + begin(a), end(a),
      begin(presum) + sz_le, op);
    le.resize(sz_le);
    ri.resize((int)size(a) - sz_le);
    transform(begin(a), begin(a) + sz_le, begin(presum),
      rbegin(le), [](T x, T y) { return dt{x, y}; });
    transform(sz_le + begin(a), end(a),
      begin(presum) + sz_le, begin(ri),
      [](T x, T y) { return dt{x, y}; });
  }
  void push_front(T elem) {
    le.push_back(
      {elem, empty(le) ? elem : op(elem, le.back()[1])});
  }
  void pop_back() {
    if (empty(ri)) {
      vector<T> a((int)size(le));
      transform(begin(le), end(le), rbegin(a),
        [](dt& x) { return x[0]; });
      rebuild(a, (int)size(a) / 2);
    }
    ri.pop_back();
  }
  T operator[](int i) {
    return (i < (int)size(le) ? le[(int)size(le) - i - 1]
                              : ri[i - (int)size(le)])[0];
  }
  T front() { return (empty(le) ? ri[0] : le.back())[0]; }
  T back() { return (empty(ri) ? le[0] : ri.back())[0]; }
};
