#pragma once
//! @code
//!   seg_tree st2(n);
//!   st2.find_last(le, ri, [&](ll x, int tl, int tr) ->
//!   bool {
//!   });
//! @endcode
//! @param le,ri defines range [le, ri)
//! @param f defines a function that returns true if the
//! subtree contains an element that satisfies the
//! condition
//!
//! guarantee: `f` is called in order on the subtrees (trs
//! are weakly decreasing) and at most once on each subtree
//!
//! if `f` returns true then every subsequent call to `f`
//! will be a subtree of the previous call; otherwise the
//! next call will be a subsequent range of the previous
//! range
//!
//! seg_tree_find.test.cpp for more details
//!
//! @returns the index of the last element in the range
//! that satisfies the condition described in `f`, if no
//! such element exists then (le - 1) is returned
//! @time O(log(n))
//! @space O(log(n)) for recursion stack
template<class F>
int find_last(int le, int ri, const F& f) {
  return find_last_in_range(le, ri, f, 0, n, 1);
}
//! invariant: f(tree[v], tl, tr) is true
template<class F>
int find_last_in_subtree(const F& f, int tl, int tr,
  int v) {
  if (v >= n) return tl;
  int tm = split(tl, tr);
  push(tl, tm, tr, v);
  if (f(tree[2 * v + 1], tm, tr))
    return find_last_in_subtree(f, tm, tr, 2 * v + 1);
  return find_last_in_subtree(f, tl, tm, 2 * v);
}
template<class F>
int find_last_in_range(int le, int ri, const F& f, int tl,
  int tr, int v) {
  if (ri <= tl || tr <= le) return le - 1;
  if (le <= tl && tr <= ri)
    return f(tree[v], tl, tr)
      ? find_last_in_subtree(f, tl, tr, v)
      : le - 1;
  int tm = split(tl, tr);
  push(tl, tm, tr, v);
  int res =
    find_last_in_range(le, ri, f, tm, tr, 2 * v + 1);
  if (res >= le) return res;
  return find_last_in_range(le, ri, f, tl, tm, 2 * v);
}
