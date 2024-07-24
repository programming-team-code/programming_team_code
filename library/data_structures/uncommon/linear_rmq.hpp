/** @file */
#pragma once
/**
 * @see On Finding Lowest Common Ancestors: Simplification and Parallelization
 * by Baruch Schieber, Uzi Vishkin, April 1987
 * @see https://codeforces.com/blog/entry/125371?#comment-1173604
 */
template <class T, class F> struct linear_rmq {
  vector<T> a;
  F cmp;
  vi head;
  vector<pii> t;
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
        int pw2 = 1 << __lg((end(st)[-2] + 1) ^ i);
        t[st.back()].first = prev = i & -pw2;
        st.pop_back();
        t[st.back() + 1].second |= pw2;
      }
      if (prev != -1) head[prev] = i;
      st.push_back(i);
    }
    rep(i, 1, sz(a))
        t[i]
            .second = (t[i].second | t[i - 1].second) & -(t[i].first & -t[i].first);
  }
  /**
   * @param le,ri defines range [min(le, ri), max(le, ri)]
   * @returns index of min/max of range
   * @time O(1)
   * @space O(1)
   */
  int query_idx(int le, int ri) {
    auto j = t[le].second & t[ri].second & -(1 << __lg((t[le].first ^ t[ri].first) | 1));
    if (auto k = t[le].second ^ j; k) k = 1 << __lg(k), le = head[(t[le].first & -k) | k];
    if (auto k = t[ri].second ^ j; k) k = 1 << __lg(k), ri = head[(t[ri].first & -k) | k];
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
