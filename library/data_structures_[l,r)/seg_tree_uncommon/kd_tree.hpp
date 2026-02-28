#pragma once
using T = int64_t;
const T unit = LLONG_MIN;
T op(T a, T b) { return max(a, b); }
template<int K> struct KD_SEG {
  int n;
  vector<KD_SEG<K - 1>> s;
  KD_SEG(int n, auto... a):
    n(n), s(2 * n, KD_SEG<K - 1>(a...)) {}
  void update(int i, auto... a) {
    s[i += n].update(a...);
    while (i /= 2) s[i].pull(s[2 * i], s[2 * i + 1], a...);
  }
  void pull(const KD_SEG<K>& l, const KD_SEG<K>& r, int i,
    auto... a) {
    s[i += n].pull(l.s[i], r.s[i], a...);
    while (i /= 2) s[i].pull(s[2 * i], s[2 * i + 1], a...);
  }
  T query(int l, int r, auto... a) {
    T x = unit, y = unit;
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
      if (l % 2) x = op(x, s[l++].query(a...));
      if (r % 2) y = op(s[--r].query(a...), y);
    }
    return op(x, y);
  }
};
template<> struct KD_SEG<0> {
  T val = unit;
  void update(T v) { val = v; }
  T query() { return val; }
  void pull(const KD_SEG<0>& l, const KD_SEG<0>& r,
    auto...) {
    val = op(l.val, r.val);
  }
};
