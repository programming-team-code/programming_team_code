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
  deq(const vector<T>& a, F a_op) : op(a_op) { rebuild(a, (int)size(a) / 2); }
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
  int siz() { return (int)size(le) + (int)size(ri); }
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
      vector<T> a((int)size(ri));
      transform(begin(ri), end(ri), begin(a), [](dt& x) { return x[0]; });
      rebuild(a, ((int)size(a) + 1) / 2);
    }
    le.pop_back();
  }
  void rebuild(const vector<T>& a, int sz_le) {
    vector<T> presum((int)size(a));
    partial_sum(rend(a) - sz_le, rend(a), rend(presum) - sz_le, [&](T x, T y) { return op(y, x); });
    partial_sum(sz_le + begin(a), end(a), begin(presum) + sz_le, op);
    le.resize(sz_le);
    ri.resize((int)size(a) - sz_le);
    transform(begin(a), begin(a) + sz_le, begin(presum), rbegin(le), [](T x, T y) { return dt{x, y}; });
    transform(sz_le + begin(a), end(a), begin(presum) + sz_le, begin(ri), [](T x, T y) { return dt{x, y}; });
  }
  /**
   * @param elem element to insert at beginning
   * @time O(1)
   * @space O(1)
   */
  void push_front(T elem) {
    le.push_back({elem, empty(le) ? elem : op(elem, le.back()[1])});
  }
  /**
   * remove deq.back()
   * @time O(1) ammortized
   * @space O(1) ammortized
   */
  void pop_back() {
    if (empty(ri)) {
      vector<T> a((int)size(le));
      transform(begin(le), end(le), rbegin(a), [](dt& x) { return x[0]; });
      rebuild(a, (int)size(a) / 2);
    }
    ri.pop_back();
  }
  /**
   * @param i index
   * @returns deq[i]
   * @time O(1)
   * @space O(1)
   */
  T operator[](int i) {
    return (i < (int)size(le) ? le[(int)size(le) - i - 1] : ri[i - (int)size(le)])[0];
  }
  /**
   * @returns deq[0]
   * @time O(1)
   * @space O(1)
   */
  T front() {
    return (empty(le) ? ri[0] : le.back())[0];
  }
  /**
   * @returns deq.back()
   * @time O(1)
   * @space O(1)
   */
  T back() {
    return (empty(ri) ? le[0] : ri.back())[0];
  }
};
