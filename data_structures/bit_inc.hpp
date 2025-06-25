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
  //! Requires s[i] >= 0
  //! max j such that j<=i && query(j,j)>0, or -1
  int prev(int i) { return walk(query(i)); }
  //! Requires s[i] >= 0
  //! min j such that j>=i && query(j,j)>0, or sz(s)
  int next(int i) { return walk(query(i - 1) + 1); }
};
