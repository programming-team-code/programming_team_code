//! @code
//!   auto mono_le1 = mono_st(a, less());
//!   // less_equal(), greater(), greater_equal()
//! @endcode
//! when cmp == less():
//!   a[mono_le1[i]] < a[i]
//! @time O(n)
//! @space O(n)
template<class T, class F>
vector<int> mono_st(const vector<T>& a, F cmp) {
  vector<int> l(ssize(a));
  for (int i = 0; i < ssize(a); i++)
    for (l[i] = i - 1; l[i] >= 0 && !cmp(a[l[i]], a[i]);)
      l[i] = l[l[i]];
  return l;
}
//! https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/CompressTree.h
//! @code
//!   auto [par, orig_node] =
//!     lca.compress_tree(subset);
//! @endcode
//! par[i] = parent of i in compressed tree, par[0]==-1
//! orig_node[i] = index of node in original tree
//! @time O(|subset| log |subset|)
//! @space O(|subset|)
array<vector<int>, 2> compress_tree(vector<int> subset) {
  auto proj = [&](int v) { return t[v].in; };
  ranges::sort(subset, {}, proj);
  int siz = ssize(subset);
  for (int i = 1; i < siz; i++)
    subset.push_back(lca(subset[i - 1], subset[i]));
  ranges::sort(subset, {}, proj);
  subset.erase(unique(begin(subset), end(subset)),
    end(subset));
  return {
    mono_st(subset,
      [&](int u, int v) { return in_subtree(u, v); }),
    subset};
}
