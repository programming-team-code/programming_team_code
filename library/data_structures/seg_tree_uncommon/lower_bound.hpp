/** @file */
#pragma once
/**
 * Requires query(i, i + 1) >= 0
 * @param sum see return
 * @returns min pos such that sum of range [0, pos) >= sum (or n + 1)
 * @time O(log n)
 * @space O(1)
 */
inline int lower_bound(int64_t sum) {
  if (sum <= 0) return 0;
  if (tree[1] < sum) return n + 1;
  int tl = 0, tr = n, u = 1;
  auto pref = 0LL;
  while (tr - tl > 1) {
    int tm = split(tl, tr);
    push(tl, tm, tr, u);
    auto pref_tm = op(pref, tree[2 * u]);
    if (pref_tm < sum)
      pref = pref_tm, tl = tm, u = 2 * u + 1;
    else
      tr = tm, u *= 2;
  }
  return tr;
}
