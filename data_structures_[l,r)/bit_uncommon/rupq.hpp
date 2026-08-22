//! @code
//!   BIT bit(n);
//!   int r = bit.walk(sum);
//!   // Returns min r s.t. sum of [0,r+1) >= sum
//!   // Returns n if sum of [0,n) < sum
//!   // Returns -1 if sum <= 0
//! @endcode
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
  int64_t query(int r) {
    int64_t res = 0;
    for (; r > 0; r &= r - 1) res += s[r - 1];
    return res;
  }
  int64_t query(int l, int r) { return query(r) - query(l); }
  int walk(int64_t sum) {
    if (sum <= 0) return -1;
    int r = 0;
    for (int i = bit_floor(size(s)); i; i >>= 1)
      if (r + i <= ssize(s) && s[r + i - 1] < sum) sum -= s[(r += i) - 1];
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
