//! https://codeforces.com/blog/entry/125371?#comment-1173604
//! @code
//!   linear_rmq rmq1(a, less());          //right-most min
//!   linear_rmq rmq2(a, less_equal());    //left-most min
//!   linear_rmq rmq3(a, greater());       //right-most max
//!   linear_rmq rmq4(a, greater_equal()); //left-most max
//!   linear_rmq rmq5(a, [&](auto& x, auto& y) {
//!     return x < y;
//!   });
//! @endcode
//! @time O(n + q)
//! @space O(n)
template<class T, class F> struct linear_rmq {
  int n;
  vector<T> a;
  F cmp;
  vector<int> in, asc, head;
  linear_rmq(const vector<T>& a, F cmp):
    n(ssize(a)), a(a), cmp(cmp), in(n), asc(n),
    head(n + 1) {
    vector<int> st{-1};
    for (int i = 0; i < n + 1; i++) {
      int prev = 0;
      while (ssize(st) > 1 &&
        (i == n || !cmp(a[st.back()], a[i]))) {
        head[prev] = st.back();
        auto k = end(st)[-2] + 1u, b = bit_floor(k ^ i);
        in[st.back()] = prev = i & -b, asc[k] |= b;
        st.pop_back();
      }
      st.push_back(head[prev] = i);
    }
    for (int i = 1; i < n; i++)
      asc[i] = (asc[i] | asc[i - 1]) & -(in[i] & -in[i]);
  }
  int idx(int l, int r) { // [l, r]
    if (unsigned i = in[l] ^ in[r]; i) {
      i = asc[l] & asc[r] & -bit_floor(i);
      if (unsigned b = asc[l] ^ i; b)
        b = bit_floor(b), l = head[(in[l] & -b) | b];
      if (unsigned b = asc[r] ^ i; b)
        b = bit_floor(b), r = head[(in[r] & -b) | b];
    }
    return cmp(a[l], a[r]) ? l : r;
  }
  T query(int l, int r) { return a[idx(l, r)]; }
};
