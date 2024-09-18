#pragma once
//! @param elem element to insert at beginning
//! @time O(1)
//! @space O(1)
void push_front(T elem) {
  le.push_back(
    {elem, empty(le) ? elem : op(elem, le.back()[1])});
}
//! remove deq.back()
//! @time O(1) ammortized
//! @space O(1) ammortized
void pop_back() {
  if (empty(ri)) {
    vector<T> a(sz(le));
    transform(all(le), rbegin(a),
      [](dt& x) { return x[0]; });
    rebuild(a, sz(a) / 2);
  }
  ri.pop_back();
}
