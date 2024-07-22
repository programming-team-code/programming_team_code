/** @file */
#pragma once
int bit_floor(unsigned x) { return x ? 1 << __lg(x) : 0; }
/**
 * @see On Finding Lowest Common Ancestors: Simplification and Parallelization
 * by Baruch Schieber, Uzi Vishkin, April 1987
 * @see https://codeforces.com/blog/entry/125371?#comment-1173604
 */
template <class T, class F> struct linear_rmq {
  vector<T> a;
  F cmp;
  vi head;
  vector<array<unsigned, 2>> t;
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
  linear_rmq(const vector<T>& a_a, F a_cmp) : a(a_a), cmp(a_cmp), head(sz(a) + 1), t(sz(a)) {
    vi st{-1};
    for (int i = 0; i <= sz(a); i++) {
      int prev = -1;
      while (st.back() != -1 && (i == sz(a) || !cmp(a[st.back()], a[i]))) {
        if (prev != -1) head[prev] = st.back();
        auto pw2 = bit_floor(unsigned(end(st)[-2] + 1) ^ i);
        t[st.back()][0] = prev = i & -pw2;
        st.pop_back();
        t[st.back() + 1][1] |= pw2;
      }
      if (prev != -1) head[prev] = i;
      st.push_back(i);
    }
    rep(i, 1, sz(a))
        t[i][1] = (t[i][1] | t[i - 1][1]) & -(t[i][0] & -t[i][0]);
  }
  /**
   * @param le,ri defines range [min(le, ri), max(le, ri)]
   * @returns index of min/max of range
   * @time O(1)
   * @space O(1)
   */
  int query_idx(int le, int ri) {
    auto j = t[le][1] & t[ri][1] & -bit_floor((t[le][0] ^ t[ri][0]) | 1);
    if (auto k = t[le][1] ^ j; k) k = bit_floor(k), le = head[(t[le][0] & -k) | k];
    if (auto k = t[ri][1] ^ j; k) k = bit_floor(k), ri = head[(t[ri][0] & -k) | k];
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
