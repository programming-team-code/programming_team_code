/** @file */
#pragma once
/**
 * @param elem element to insert at beginning
 * @time O(1)
 * @space O(1)
 */
inline void push_front(T elem) {
  le.push_back({elem, empty(le) ? elem : op(elem, le.back()[1])});
}
/**
 * remove deq.back()
 * @time O(1) ammortized
 * @space O(1) ammortized
 */
inline void pop_back() {
  assert(siz());
  if (empty(ri)) {
    vector<T> a(sz(le));
    transform(begin(le), end(le), rbegin(a), [](dt& x) { return x[0]; });
    rebuild(a, sz(a) / 2);
  }
  ri.pop_back();
}
