//! @file
#pragma once
//! @code{.cpp}
//!     implicit_seg_tree<10'000'000> ist(le, ri);
//! @endcode
template <int N> struct implicit_seg_tree {
  using dt = array<ll, 2>;  //!< min, number of mins
  static dt op(const dt& le, const dt& ri) {
    if (le[0] == ri[0])
      return {le[0], le[1] + ri[1]};
    return min(le, ri);
  }
  static constexpr dt unit{LLONG_MAX, 0LL};
  struct node {
    dt num;
    ll lazy = 0;
    int lch = -1, rch = -1;
  } tree[N];
  int ptr = 0, root_l,
      root_r;  //!< [root_l, root_r) defines range
               //!< of root node; handles negatives
  implicit_seg_tree(int le, int ri)
      : root_l(le), root_r(ri) {
    tree[ptr++].num = {0, ri - le};
  }
  void apply(ll add, int v) {
    tree[v].num[0] += add;
    tree[v].lazy += add;
  }
  void push(int tl, int tm, int tr, int v) {
    if (tr - tl > 1 && tree[v].lch == -1) {
      tree[v].lch = ptr;
      tree[ptr++].num = {0, tm - tl};
      tree[v].rch = ptr;
      tree[ptr++].num = {0, tr - tm};
    }
    if (tree[v].lazy) {
      apply(tree[v].lazy, tree[v].lch);
      apply(tree[v].lazy, tree[v].rch);
      tree[v].lazy = 0;
    }
  }
  //! @param le,ri defines range [le, ri)
  void update(int le, int ri, ll add) {
    update(le, ri, add, root_l, root_r, 0);
  }
  void update(
    int le, int ri, ll add, int tl, int tr, int v) {
    if (ri <= tl || tr <= le) return;
    if (le <= tl && tr <= ri) return apply(add, v);
    int tm = tl + (tr - tl) / 2;
    push(tl, tm, tr, v);
    update(le, ri, add, tl, tm, tree[v].lch);
    update(le, ri, add, tm, tr, tree[v].rch);
    tree[v].num = op(
      tree[tree[v].lch].num, tree[tree[v].rch].num);
  }
  //! @param le,ri defines range [le, ri)
  dt query(int le, int ri) {
    return query(le, ri, root_l, root_r, 0);
  }
  dt query(int le, int ri, int tl, int tr, int v) {
    if (ri <= tl || tr <= le) return unit;
    if (le <= tl && tr <= ri) return tree[v].num;
    int tm = tl + (tr - tl) / 2;
    push(tl, tm, tr, v);
    return op(query(le, ri, tl, tm, tree[v].lch),
      query(le, ri, tm, tr, tree[v].rch));
  }
};
