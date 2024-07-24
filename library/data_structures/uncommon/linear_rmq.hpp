/** @file */
#pragma once
/**
 * @see On Finding Lowest Common Ancestors: Simplification and Parallelization
 * by Baruch Schieber, Uzi Vishkin, April 1987
 * @see https://codeforces.com/blog/entry/125371?#comment-1173604
 */
template <class T, class F> struct linear_rmq {
  vector<T> a;
  int n;
  F cmp;
  vi label, asc, head;
  /**
   * @code{.cpp}
         vector<ll> a(n);
         linear_rmq rmq(a, less()); // right-most min
         linear_rmq rmq(a, less_equal()); // left-most min
         linear_rmq rmq(a, greater()); // right-most max
         linear_rmq rmq(a, greater_equal()); // left-most max
   * @endcode
   * @param a_a,a_cmp array and a compare operator
   * @time O(n)
   * @space O(n)
   */
  linear_rmq(const vector<T>& a_a, F a_cmp) : a(a_a), n(sz(a)), cmp(a_cmp), label(n), asc(n), head(n + 1) {
    vi st{-1};
    for (int i = 0; i <= n; i++) {
      int prev = -1;
      while (st.back() != -1 && (i == n || !cmp(a[st.back()], a[i]))) {
        if (prev != -1) head[prev] = st.back();
        int pw2 = 1 << __lg((end(st)[-2] + 1) ^ i);
        label[st.back()] = prev = i & -pw2;
        st.pop_back();
        asc[st.back() + 1] |= pw2;
      }
      if (prev != -1) head[prev] = i;
      st.push_back(i);
    }
    rep(i, 1, n)
        asc[i] = (asc[i] | asc[i - 1]) & -(label[i] & -label[i]);
  }
  /**
   * @param le,ri defines range [min(le, ri), max(le, ri)]
   * @returns index of min/max of range
   * @time O(1)
   * @space O(1)
   */
  int query_idx(int le, int ri) {
    int j = asc[le] & asc[ri] & -(1 << __lg((label[le] ^ label[ri]) | 1));
    if (int k = asc[le] ^ j; k) k = 1 << __lg(k), le = head[(label[le] & -k) | k];
    if (int k = asc[ri] ^ j; k) k = 1 << __lg(k), ri = head[(label[ri] & -k) | k];
    return cmp(a[le], a[ri]) ? le : ri;
  }
  /**
   * @param le,ri defines range [min(le, ri), max(le, ri)]
   * @returns min/max of range
   * @time O(1)
   * @space O(1)
   */
  T query(int le, int ri) { return a[query_idx(le, ri)]; }
};
