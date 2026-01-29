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
    int64_t ret = 0;
    for (; r > 0; r &= r - 1) ret += s[r - 1];
    return ret;
  }
  int64_t query(int l, int r) {
    return query(r) - query(l);
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
//! https://blog.mitrichev.ch/2013/05/fenwick-tree-range-updates.html
struct bit_rurq {
  int n;
  BIT bit1 = {0}, bit2 = {0};
  bit_rurq(int n): n(n), bit1(n), bit2(n) {}
  bit_rurq(vector<int64_t> a): n(ssize(a)) {
    adjacent_difference(begin(a), end(a), begin(a));
    bit1 = {a};
    for (int i = 0; i < n; i++) a[i] *= i;
    bit2 = {a};
  }
  //! does a[l]+=d, a[l+1]+=d, ..., a[r-1]+=d
  //! @time O(log n)
  //! @space O(1)
  void update(int l, int r, int64_t d) {
    if (l < n) {
      bit1.update(l, d);
      bit2.update(l, d * l);
    }
    if (r < n) {
      bit1.update(r, -d);
      bit2.update(r, -d * r);
    }
  }
  //! @returns a[0]+a[1]+...+a[r-1]
  //! @time O(log n)
  //! @space O(1)
  int64_t query(int r) {
    return bit1.query(r) * r - bit2.query(r);
  }
  //! @returns a[l]+a[l+1]+...+a[r-1]
  //! @time O(log n)
  //! @space O(1)
  int64_t query(int l, int r) {
    return query(r) - query(l);
  }
};
