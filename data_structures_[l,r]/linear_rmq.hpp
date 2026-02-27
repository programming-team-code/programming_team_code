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
        auto j = end(st)[-2] + 1u, k = bit_floor(i ^ j);
        in[st.back()] = prev = i & -k, asc[j] |= k;
        st.pop_back();
      }
      st.push_back(head[prev] = i);
    }
    for (int i = 1; i < n; i++)
      asc[i] = (asc[i] | asc[i - 1]) & -(in[i] & -in[i]);
  }
  int idx(int l, int r) {
    if (unsigned j = in[l] ^ in[r]; j) {
      j = asc[l] & asc[r] & -bit_floor(j);
      if (unsigned k = asc[l] ^ j; k)
        k = bit_floor(k), l = head[(in[l] & -k) | k];
      if (unsigned k = asc[r] ^ j; k)
        k = bit_floor(k), r = head[(in[r] & -k) | k];
    }
    return cmp(a[l], a[r]) ? l : r;
  }
  T query(int l, int r) { return a[idx(l, r)]; }
};
