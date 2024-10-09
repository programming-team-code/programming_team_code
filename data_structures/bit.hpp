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
