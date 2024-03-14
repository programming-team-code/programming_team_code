/** @file */
#pragma once
/**
 * @param le,ri defines range [le, ri)
 * @param f defines a function that returns true if the subtree contains an
 * element that satisfies the condition
 * @returns the index of the first element in the range that satisfies the
 * condition described in `f`, if no such element exists then `ri` is returned
 * @time O(log(n))
 * @space O(log(n)) for recursion stack; no new nodes are allocated
 */
template <class F>
int find_first(int le, int ri, const F& f) {
  return find_first_impl(le, ri, f, 0, n, 1);
}
template <class F>
int find_first_impl(int le, int ri, const F& f, int tl, int tr, int u) {
  if (ri <= tl || tr <= le) return ri;
  if (tr - tl == 1) {
    if (f(tree[u], tl, tr)) return tl;
    return ri;
  }
  int tm = split(tl, tr);
  push(tl, tm, tr, u);
  if (le <= tl && tr <= ri) {
    if (!f(tree[u], tl, tr)) return ri;
    if (f(tree[2 * u], tl, tm))
      return find_first_impl(le, ri, f, tl, tm, 2 * u);
    return find_first_impl(le, ri, f, tm, tr, 2 * u + 1);
  }
  return min(find_first_impl(le, ri, f, tl, tm, 2 * u),
             find_first_impl(le, ri, f, tm, tr, 2 * u + 1));
}
