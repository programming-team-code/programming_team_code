//! https://codeforces.com/blog/entry/125371?#comment-1173604
//! @code
//!   linear_rmq rmq1(a, less());//right-most min
//!   linear_rmq rmq2(a, less_equal());//left-most min
//!   linear_rmq rmq3(a, greater());//right-most max
//!   linear_rmq rmq4(a, greater_equal());//left-most max
//!   linear_rmq rmq5(a, [&](auto& x, auto& y) {
//!     return x < y;
//!   });
//! @endcode
//! @time O(n + q)
//! @space O(n)
template<class T, class F> struct linear_rmq {
  vector<T> a;
  F cmp;
  vector<int> head;
  vector<array<int, 2>> t;
  linear_rmq(const vector<T>& a, F cmp):
    a(a), cmp(cmp), head(ssize(a) + 1), t(ssize(a)) {
    vector<int> st{-1};
    for (int i = 0; i <= ssize(a); i++) {
      int prev = -1;
      while (st.back() != -1 &&
        (i == ssize(a) || !cmp(a[st.back()], a[i]))) {
        if (prev != -1) head[prev] = st.back();
        int pw2 = 1 << __lg((end(st)[-2] + 1) ^ i);
        t[st.back()][0] = prev = i & -pw2;
        st.pop_back();
        t[st.back() + 1][1] |= pw2;
      }
      if (prev != -1) head[prev] = i;
      st.push_back(i);
    }
    for (int i = 1; i < ssize(a); i++)
      t[i][1] =
        (t[i][1] | t[i - 1][1]) & -(t[i][0] & -t[i][0]);
  }
  int query_idx(int l, int r) { // [l, r]
    if (unsigned j = t[l][0] ^ t[r][0]; j) {
      j = t[l][1] & t[r][1] & -bit_floor(j);
      if (unsigned k = t[l][1] ^ j; k)
        k = bit_floor(k), l = head[(t[l][0] & -k) | k];
      if (unsigned k = t[r][1] ^ j; k)
        k = bit_floor(k), r = head[(t[r][0] & -k) | k];
    }
    return cmp(a[l], a[r]) ? l : r;
  }
  T query(int l, int r) { return a[query_idx(l, r)]; }
};
