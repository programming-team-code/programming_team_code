//! https://codeforces.com/blog/entry/153134
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
  vector<T> a;
  F cmp;
  vector<int> asc, head;
  linear_rmq(const vector<T>& a, F cmp): a(a), cmp(cmp), asc(ssize(a)), head(asc) {
    vector<int> st{-1};
    for (int i = 0; i < ssize(a); i++) {
      int prev = i;
      while (ssize(st) > 1 && !cmp(a[st.back()], a[i])) {
        auto j = end(st)[-2] + 1u, k = bit_floor(i ^ j);
        head[prev = i & -k] = j - 1;
        asc[j] |= k, asc[st.back()] |= k;
        st.pop_back();
      }
      st.push_back(head[prev] = i);
    }
    for (int i = 1; i < ssize(a); i++) asc[i] |= asc[i - 1] & -asc[i];
  }
  int idx(int l, int r) {
    if (l == r) return l;
    auto j = asc[l] & asc[r] & -bit_floor(l ^ r ^ 0u);
    if (int k = bit_floor(asc[l] ^ j)) l = head[(l & -k) | k];
    if (int k = bit_floor(asc[r] ^ j)) r = head[(r & -k) | k];
    return cmp(a[l], a[r]) ? l : r;
  }
  T query(int l, int r) { return a[idx(l, r)]; }
};
