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
  int64_t query(int i) {
    int64_t ret = 0;
    for (; i >= 0; (i &= i + 1)--) ret += s[i];
    return ret;
  }
  int64_t query(int l, int r) {
    return query(r) - query(l - 1);
  }
  //! Requires sum of [i,i] >= 0
  //! Returns min r s.t. sum of [0,r] >= sum
  //! Returns n if sum of [0,n-1] < sum
  int walk(int64_t sum) {
    if (sum <= 0) return -1;
    int r = 0;
    for (int i = bit_floor(size(s)); i; i /= 2)
      if (r + i <= ssize(s) && s[r + i - 1] < sum)
        sum -= s[(r += i) - 1];
    return r;
  }
};
