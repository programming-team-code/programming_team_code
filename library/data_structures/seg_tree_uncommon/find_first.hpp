#pragma once
//! @code
//!   seg_tree st1(n);
//!   st1.find_first(le, ri, [&](ll x, int tl, int tr) ->
//!   bool {
//!   });
//! @endcode
//! @param le,ri defines range [le, ri)
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
//! such element exists then `ri` is returned
//! @time O(log(n))
//! @space O(log(n)) for recursion stack
template <class F>
int find_first(int le, int ri, const F& f) {
  return find_first_in_range(le, ri, f, 0, n, 1);
}
//! invariant: f(tree[v], tl, tr) is 1
template <class F>
int find_first_in_subtree(const F& f, int tl, int tr,
                          int v) {
  if (v >= n) return tl;
  int tm = split(tl, tr);
  push(tl, tm, tr, v);
  if (f(tree[2 * v], tl, tm))
    return find_first_in_subtree(f, tl, tm, 2 * v);
  return find_first_in_subtree(f, tm, tr, 2 * v + 1);
}
template <class F>
int find_first_in_range(int le, int ri, const F& f, int tl,
                        int tr, int v) {
  if (ri <= tl || tr <= le) return ri;
  if (le <= tl && tr <= ri)
    return f(tree[v], tl, tr)
               ? find_first_in_subtree(f, tl, tr, v)
               : ri;
  int tm = split(tl, tr);
  push(tl, tm, tr, v);
  int res = find_first_in_range(le, ri, f, tl, tm, 2 * v);
  if (res < ri) return res;
  return find_first_in_range(le, ri, f, tm, tr, 2 * v + 1);
}
