/** @file */
#pragma once
/**
 * @param le,ri defines range [le, ri)
 * @param f(tree[u], tl, tr) defines a function that returns true if the subtree
 * contains an element that satisfies the condition
 * @returns the index of the first element in the range that satisfies the
 * condition described in `f`, if no such element exists then `ri` is returned
 * @time O(log(n))
 * @space O(log(n)) for recursion stack; no new nodes are allocated
 */
int find_first(int le, int ri, function<bool(int64_t, int, int)> f) {
	return find_first(le, ri, f, 0, n, 1);
}
int find_first(int le, int ri, const function<bool(int64_t, int, int)>& f,
               int tl, int tr, int u) {
	if (ri <= tl || tr <= le) return ri;
	if (tr - tl == 1) {
		if (f(tree[u], tl, tr)) return tl;
		return ri;
	}
	int tm = split(tl, tr);
	push(tl, tm, tr, u);
	if (le <= tl && tr <= ri) {
		if (!f(tree[u], tl, tr)) return ri;
		if (f(tree[2 * u], tl, tm)) return find_first(le, ri, f, tl, tm, 2 * u);
		return find_first(le, ri, f, tm, tr, 2 * u + 1);
	}
	return min(find_first(le, ri, f, tl, tm, 2 * u),
	           find_first(le, ri, f, tm, tr, 2 * u + 1));
}
