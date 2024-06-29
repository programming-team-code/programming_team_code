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
  UF(int n) : e(n, -1) {}
  bool sameSet(int a, int b) { return find(a) == find(b); }
  int size(int x) { return -e[find(x)]; }
  int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
  bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (e[a] > e[b]) swap(a, b);
    e[a] += e[b];
    e[b] = a;
    return true;
  }
};
/**
 * DSU with support for joining two parallel ranges [l1, l1 + len) and [l2, l2 +
 * len) such that edges of the form (l1 + i, l2 + i) are joined. for all `i` in
 * [0, len).
 *
 * @time O(n * log n * inverse ack n) amortized across all queries
 * @space O(n log n)
 */
struct range_parallel_dsu {
  vector<UF> ufs;
  /*
   * constructs a range_parallel_dsu with n elements.
   */
  range_parallel_dsu(int n) : ufs(__lg(n) + 1, UF(n)) {}
  /*
   * joins the ranges [l1, l1 + len) and [l2, l2 + len) such that edges of the
   * form (l1 + i, l2 + i) are joined. for all `i` in [0, len). The function `f`
   * is called for each connected component of the resulting graph which will
   * change in this update, with the first argument being the representative of
   * the component and the second argument being the parent of the component
   * which is being joined.
   *
   * @guarantee the function `f` is called at most `n - 1` times
   *
   * @time O(n * log n * inverse ack) amortized across all queries
   * @space O(log n) due to the recursive stack
   */
  template <class F>
  void join(int l1, int l2, int len, const F& f) {
    if (len == 0) return;
    int lg = __lg(len);
    join_impl(lg, l1, l2, f);
    join_impl(lg, l1 + len - (1 << lg), l2 + len - (1 << lg), f);
  }
  template <class F>
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
    join_impl(lvl - 1, u + (1 << (lvl - 1)), v + (1 << (lvl - 1)), f);
  }
};
