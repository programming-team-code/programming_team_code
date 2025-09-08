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
  //! max r such that sum of [0,r) < sum, or -1
  int walk(int64_t sum) {
    if (sum <= 0) return -1;
    int r = 0;
    for (int pw = bit_floor(size(s)); pw; pw >>= 1)
      if (r + pw <= ssize(s) && s[r + pw - 1] < sum)
        sum -= s[(r += pw) - 1];
    return r;
  }
};
struct bit_rupq {
  int n;
  BIT bit = {0};
  bit_rupq(int n): n(n), bit(n) {}
  bit_rupq(vector<int64_t> a): n(ssize(a)) {
    adjacent_difference(begin(a), end(a), begin(a));
    bit = {a};
  }
  //! does a[l]+=d, a[l+1]+=d, .., a[r-1]+=d
  //! @time O(log n)
  //! @space O(1)
  void update(int l, int r, int64_t d) {
    if (l < n) bit.update(l, d);
    if (r < n) bit.update(r, -d);
  }
  //! @returns a[i]
  //! @time O(log n)
  //! @space O(1)
  int64_t get_index(int i) { return bit.query(i + 1); }
};
