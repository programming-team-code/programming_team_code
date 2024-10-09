//! https://codeforces.com/blog/entry/125371?#comment-1173604
//! @code
//!   linear_rmq r1(a, less());//right-most min
//!   linear_rmq r2(a, less_equal());//left-most min
//!   linear_rmq r3(a, greater());//right-most max
//!   linear_rmq r4(a, greater_equal());//left-most max
//!   linear_rmq r5(a, [&](auto& x, auto& y) {
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
  linear_rmq(const vector<T>& a_a, F a_cmp):
    a(a_a), cmp(a_cmp), head((int)size(a) + 1),
    t((int)size(a)) {
    vector<int> st{-1};
    for (int i = 0; i <= (int)size(a); i++) {
      int prev = -1;
      while (st.back() != -1 &&
        (i == (int)size(a) || !cmp(a[st.back()], a[i]))) {
        if (prev != -1) head[prev] = st.back();
        int pw2 = 1 << __lg((end(st)[-2] + 1) ^ i);
        t[st.back()][0] = prev = i & -pw2;
        st.pop_back();
        t[st.back() + 1][1] |= pw2;
      }
      if (prev != -1) head[prev] = i;
      st.push_back(i);
    }
    for (int i = 1; i < ((int)size(a)); i++)
      t[i][1] =
        (t[i][1] | t[i - 1][1]) & -(t[i][0] & -t[i][0]);
  }
  int query_idx(int le, int ri) { // [le, ri]
    if (int j = t[le][0] ^ t[ri][0]; j) {
      j = t[le][1] & t[ri][1] & -(1 << __lg(j));
      if (int k = t[le][1] ^ j; k)
        k = 1 << __lg(k), le = head[(t[le][0] & -k) | k];
      if (int k = t[ri][1] ^ j; k)
        k = 1 << __lg(k), ri = head[(t[ri][0] & -k) | k];
    }
    return cmp(a[le], a[ri]) ? le : ri;
  }
  T query(int le, int ri) { return a[query_idx(le, ri)]; }
};
