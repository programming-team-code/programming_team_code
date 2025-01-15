//! @time O(n + q log n)
//! @space O(n)
struct BIT {
  vector<int64_t> s;
  BIT(int n): s(n) {}
  BIT(const vector<int64_t>& a): s(a) {
    for (int i = 0; i < ssize(a); i++) {
      int j = i | (i + 1);
      if (j < ssize(a)) s[j] += s[i];
    }
  }
  void update(int i, int64_t d) {
    for (; i < ssize(s); i |= i + 1) s[i] += d;
  }
  int64_t query(int r) { // [0, r)
    int64_t ret = 0;
    for (; r > 0; r &= r - 1) ret += s[r - 1];
    return ret;
  }
  int64_t query(int l, int r) { // [l, r)
    return query(r) - query(l);
  }
  //! Requires s[i] >= 0
  //! max pos such that sum of [0,pos) < sum, or -1
  int walk(int64_t sum) {
    if (sum <= 0) return -1;
    int pos = 0;
    for (int pw = bit_floor(size(s)); pw; pw >>= 1)
      if (pos + pw <= ssize(s) && s[pos + pw - 1] < sum)
        pos += pw, sum -= s[pos - 1];
    return pos;
  }
};
