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
