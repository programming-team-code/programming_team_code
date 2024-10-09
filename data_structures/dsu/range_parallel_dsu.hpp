/**
 * Author: Lukas Polacek
 * Date: 2009-10-26
 * License: CC0
 * Source: folklore
 * Description: Disjoint-set data structure.
 * Time: $O(\alpha(N))$
 */
struct UF {
  vector<int> e;
  UF(int n): e(n, -1) {}
  bool sameSet(int a, int b) { return find(a) == find(b); }
  int size(int x) { return -e[find(x)]; }
  int find(int x) {
    return e[x] < 0 ? x : e[x] = find(e[x]);
  }
  bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (e[a] > e[b]) swap(a, b);
    e[a] += e[b];
    e[b] = a;
    return true;
  }
};
//! Given l1,l2,len; joins (l1,l2), (l1+1,l2+1),
//!   ..., (l1+len-1,l2+len-1)
//! `f` is called at most n-1 times
//! @time O(n*log(n)*\alpha(n) + q)
//! @space O(n log n)
struct rp_dsu {
  vector<UF> ufs;
  rp_dsu(int n): ufs(__lg(n) + 1, UF(n)) {}
  template<class F>
  void join(int l1, int l2, int len, const F& f) {
    if (len == 0) return;
    int lg = __lg(len);
    join_impl(lg, l1, l2, f);
    join_impl(lg, l1 + len - (1 << lg),
      l2 + len - (1 << lg), f);
  }
  template<class F>
  void join_impl(int lvl, int u, int v, const F& f) {
    if (lvl == 0) {
      u = ufs[0].find(u);
      v = ufs[0].find(v);
      if (!ufs[0].join(v, u)) return;
      int w = ufs[0].find(u);
      return f(w, u ^ v ^ w);
    }
    if (!ufs[lvl].join(u, v)) return;
    join_impl(lvl - 1, u, v, f);
    join_impl(lvl - 1, u + (1 << (lvl - 1)),
      v + (1 << (lvl - 1)), f);
  }
};
