#pragma once
void push_front(T elem) {
  l.push_back(
    {elem, empty(l) ? elem : op(elem, l.back()[1])});
}
void pop_back() {
  if (empty(r)) {
    vector<T> a(sz(l));
    transform(all(l), rbegin(a),
      [](dt& x) { return x[0]; });
    rebuild(a, sz(a) / 2);
  }
  r.pop_back();
}
