#pragma once
//! @code
//!     implicit_seg_tree<10'000'000> ist(l, r);
//! @endcode
template<int N> struct implicit_seg_tree {
  using dt = array<ll, 2>; //!< min, number of mins
  static dt op(const dt& l, const dt& r) {
    if (l[0] == r[0]) return {l[0], l[1] + r[1]};
    return min(l, r);
  }
  const dt unit{LLONG_MAX, 0LL};
  struct node {
    dt num;
    ll lazy = 0;
    int lch = -1, rch = -1;
  } tree[N];
  int ptr = 0, root_l, root_r;
  implicit_seg_tree(int l, int r): root_l(l), root_r(r) {
    tree[ptr++].num = {0, r - l};
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
  void update(int l, int r, ll add) { // [l, r)
    update(l, r, add, root_l, root_r, 0);
  }
  void update(int l, int r, ll add, int tl, int tr,
    int v) {
    if (r <= tl || tr <= l) return;
    if (l <= tl && tr <= r) return apply(add, v);
    int tm = tl + (tr - tl) / 2;
    push(tl, tm, tr, v);
    update(l, r, add, tl, tm, tree[v].lch);
    update(l, r, add, tm, tr, tree[v].rch);
    tree[v].num =
      op(tree[tree[v].lch].num, tree[tree[v].rch].num);
  }
  dt query(int l, int r) { // [l, r)
    return query(l, r, root_l, root_r, 0);
  }
  dt query(int l, int r, int tl, int tr, int v) {
    if (r <= tl || tr <= l) return unit;
    if (l <= tl && tr <= r) return tree[v].num;
    int tm = tl + (tr - tl) / 2;
    push(tl, tm, tr, v);
    return op(query(l, r, tl, tm, tree[v].lch),
      query(l, r, tm, tr, tree[v].rch));
  }
};
