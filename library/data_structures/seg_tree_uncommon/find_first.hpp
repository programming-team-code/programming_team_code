#pragma once
//! @code
//!   seg_tree st1(n);
//!   st1.find_first(l, r, [&](ll x, int tl, int tr) ->
//!   bool {
//!   });
//! @endcode
//! @param l,r defines range [l, r)
//! @param f defines a function that returns 1 if the
//! subtree contains an element that satisfies the
//! condition
//!
//! guarantee: `f` is called in order on the subtrees (tls
//! are weakly increasing) and at most once on each subtree
//!
//! if `f` returns 1 then every subsequent call to `f`
//! will be a subtree of the previous call; otherwise the
//! next call will be a subsequent range of the previous
//! range
//!
//! seg_tree_find.test.cpp for more details
//!
//! @returns the index of the first element in the range
//! that satisfies the condition described in `f`, if no
//! such element exists then `r` is returned
//! @time O(log(n))
//! @space O(log(n)) for recursion stack
template<class F>
int find_first(int l, int r, const F& f) {
  return find_first_in_range(l, r, f, 0, n, 1);
}
//! invariant: f(tree[v], tl, tr) is 1
template<class F>
int find_first_in_subtree(const F& f, int tl, int tr,
  int v) {
  if (v >= n) return tl;
  int tm = split(tl, tr);
  push(tl, tm, tr, v);
  if (f(tree[2 * v], tl, tm))
    return find_first_in_subtree(f, tl, tm, 2 * v);
  return find_first_in_subtree(f, tm, tr, 2 * v + 1);
}
template<class F>
int find_first_in_range(int l, int r, const F& f, int tl,
  int tr, int v) {
  if (r <= tl || tr <= l) return r;
  if (l <= tl && tr <= r)
    return f(tree[v], tl, tr)
      ? find_first_in_subtree(f, tl, tr, v)
      : r;
  int tm = split(tl, tr);
  push(tl, tm, tr, v);
  int res = find_first_in_range(l, r, f, tl, tm, 2 * v);
  if (res < r) return res;
  return find_first_in_range(l, r, f, tm, tr, 2 * v + 1);
}
