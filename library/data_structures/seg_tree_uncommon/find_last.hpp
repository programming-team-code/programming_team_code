/** @file */
#pragma once
/**
 * @param le,ri defines range [le, ri)
 * @param f defines a function that returns true if the subtree contains an
 * element that satisfies the condition
 * @returns the index of the last element in the range that satisfies the
 * condition described in `f`, if no such element exists then (le - 1) is
 * returned
 * @time O(log(n))
 * @space O(log(n)) for recursion stack
 */
template <class F>
int find_last(int le, int ri, const F& f) {
  return find_last_impl(le, ri, f, 0, n, 1);
}
template <class F>
int find_last_impl(int le, int ri, const F& f, int tl, int tr, int u) {
  if (ri <= tl || tr <= le) return le - 1;
  if (u >= n) {
    if (f(tree[u], tl, tr)) return tl;
    return le - 1;
  }
  int tm = split(tl, tr);
  push(tl, tm, tr, u);
  if (le <= tl && tr <= ri) {
    if (f(tree[2 * u + 1], tm, tr))
      return find_last_impl(le, ri, f, tm, tr, 2 * u + 1);
    if (f(tree[2 * u], tl, tm)) return find_last_impl(le, ri, f, tl, tm, 2 * u);
    return le - 1;
  }
  int res = find_last_impl(le, ri, f, tm, tr, 2 * u + 1);
  if (res >= le) return res;
  return find_last_impl(le, ri, f, tl, tm, 2 * u);
}
