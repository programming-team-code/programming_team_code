/** @file */
#pragma once
/**
 * @code{.cpp}
       implicit_seg_tree<10'000'000> ist(le, ri);
 * @endcode
 */
template <int N> struct implicit_seg_tree {
  using dt = array<ll, 2>; /**< min, number of mins */
  static dt op(const dt& le, const dt& ri) {
    if (le[0] == ri[0]) return {le[0], le[1] + ri[1]};
    return min(le, ri);
  }
  static constexpr dt unit{LLONG_MAX, 0LL};
  struct node {
    dt num;
    ll lazy = 0;
    int lch = -1, rch = -1;
  } tree[N];
  int ptr = 0, root_l, root_r; /**< [root_l, root_r) defines range of root node; handles negatives */
  implicit_seg_tree(int le, int ri) : root_l(le), root_r(ri) {
    tree[ptr++].num = {0, ri - le};
  }
  void apply(ll add, int u) {
    tree[u].num[0] += add;
    tree[u].lazy += add;
  }
  void push(int tl, int tm, int tr, int u) {
    if (tr - tl > 1 && tree[u].lch == -1) {
      assert(ptr + 1 < N);
      tree[u].lch = ptr;
      tree[ptr++].num = {0, tm - tl};
      tree[u].rch = ptr;
      tree[ptr++].num = {0, tr - tm};
    }
    if (tree[u].lazy) {
      apply(tree[u].lazy, tree[u].lch);
      apply(tree[u].lazy, tree[u].rch);
      tree[u].lazy = 0;
    }
  }
  /**
   * @param le,ri defines range [le, ri)
   */
  void update(int le, int ri, ll add) { update(le, ri, add, root_l, root_r, 0); }
  void update(int le, int ri, ll add, int tl, int tr, int u) {
    if (ri <= tl || tr <= le)
      return;
    if (le <= tl && tr <= ri)
      return apply(add, u);
    int tm = tl + (tr - tl) / 2;
    push(tl, tm, tr, u);
    update(le, ri, add, tl, tm, tree[u].lch);
    update(le, ri, add, tm, tr, tree[u].rch);
    tree[u].num = op(tree[tree[u].lch].num,
                     tree[tree[u].rch].num);
  }
  /**
   * @param le,ri defines range [le, ri)
   */
  dt query(int le, int ri) { return query(le, ri, root_l, root_r, 0); }
  dt query(int le, int ri, int tl, int tr, int u) {
    if (ri <= tl || tr <= le)
      return unit;
    if (le <= tl && tr <= ri)
      return tree[u].num;
    int tm = tl + (tr - tl) / 2;
    push(tl, tm, tr, u);
    return op(query(le, ri, tl, tm, tree[u].lch),
              query(le, ri, tm, tr, tree[u].rch));
  }
};
