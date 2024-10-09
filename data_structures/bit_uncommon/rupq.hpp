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
template<class T> struct bit_rupq {
  int n;
  BIT<T> bit = {0};
  bit_rupq(int a_n): n(a_n), bit(n) {}
  bit_rupq(vector<T> a): n((int)size(a)) {
    adjacent_difference(begin(a), end(a), begin(a));
    bit = {a};
  }
  //! does a[le]+=d, a[le+1]+=d, .., a[ri-1]+=d
  //! @time O(log n)
  //! @space O(1)
  void update(int le, int ri, T d) {
    if (le < n) bit.update(le, d);
    if (ri < n) bit.update(ri, -d);
  }
  //! @returns a[i]
  //! @time O(log n)
  //! @space O(1)
  T get_index(int i) { return bit.query(i + 1); }
};
