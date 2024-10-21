//! @time O(n + q log n)
//! @space O(n)
struct bit_inc {
  vector<int64_t> s;
  bit_inc(int n): s(n) {}
  void update(int i, int64_t d) {
    for (; i < ssize(s); i |= i + 1) s[i] += d;
  }
  int64_t query(int i) { // [0, i]
    int64_t ret = 0;
    for (; i >= 0; (i &= i + 1)--) ret += s[i];
    return ret;
  }
  int64_t query(int l, int r) { // [l, r]
    return query(r) - query(l - 1);
  }
};
