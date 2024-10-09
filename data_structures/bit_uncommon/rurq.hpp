//! @code
//!   BIT<int> bit1(n);
//!   BIT<ll> bit2(n);
//! @endcode
//! @time O(n + q log n)
//! @space O(n)
template<class T> struct BIT {
  vector<T> s;
  BIT(int n): s(n) {}
  BIT(const vector<T>& a): s(a) {
    for (int i = 0; i < ((int)size(a)); i++) {
      int j = i | (i + 1);
      if (j < (int)size(a)) s[j] += s[i];
    }
  }
  void update(int i, T d) {
    for (; i < (int)size(s); i |= i + 1) s[i] += d;
  }
  T query(int ri) { // [0, ri)
    T ret = 0;
    for (; ri > 0; ri &= ri - 1) ret += s[ri - 1];
    return ret;
  }
  T query(int le, int ri) { // [le, ri)
    return query(ri) - query(le);
  }
  //! Requires bit.query(i,i+1) >= 0
  //! @returns max pos such that sum of [0,pos) < sum
  int lower_bound(T sum) {
    if (sum <= 0) return -1;
    int pos = 0;
    for (int pw = 1 << __lg((int)size(s) | 1); pw;
         pw >>= 1)
      if (
        pos + pw <= (int)size(s) && s[pos + pw - 1] < sum)
        pos += pw, sum -= s[pos - 1];
    return pos;
  }
};
//! https://blog.mitrichev.ch/2013/05/fenwick-tree-range-updates.html
template<class T> struct bit_rurq {
  int n;
  BIT<T> bit1 = {0}, bit2 = {0};
  bit_rurq(int a_n): n(a_n), bit1(n), bit2(n) {}
  bit_rurq(vector<T> a): n((int)size(a)) {
    adjacent_difference(begin(a), end(a), begin(a));
    bit1 = {a};
    for (int i = 0; i < (n); i++) a[i] *= i;
    bit2 = {a};
  }
  //! does a[le]+=d, a[le+1]+=d, ..., a[ri-1]+=d
  //! @time O(log n)
  //! @space O(1)
  void update(int le, int ri, T d) {
    if (le < n) {
      bit1.update(le, d);
      bit2.update(le, d * le);
    }
    if (ri < n) {
      bit1.update(ri, -d);
      bit2.update(ri, -d * ri);
    }
  }
  //! @returns a[0]+a[1]+...+a[ri-1]
  //! @time O(log n)
  //! @space O(1)
  T query(int ri) {
    return bit1.query(ri) * ri - bit2.query(ri);
  }
  //! @returns a[le]+a[le+1]+...+a[ri-1]
  //! @time O(log n)
  //! @space O(1)
  T query(int le, int ri) { return query(ri) - query(le); }
};
