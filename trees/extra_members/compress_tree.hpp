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
  vector<int> le((int)size(a));
  for (int i = 0; i < ((int)size(a)); i++)
    for (le[i] = i - 1;
         le[i] >= 0 && !cmp(a[le[i]], a[i]);)
      le[i] = le[le[i]];
  return le;
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
  auto cmp = [&](int u, int v) {
    return t[u].in < t[v].in;
  };
  sort(begin(subset), end(subset), cmp);
  int siz = (int)size(subset);
  for (int i = 1; i < (siz); i++)
    subset.push_back(lca(subset[i - 1], subset[i]));
  sort(begin(subset), end(subset), cmp);
  subset.erase(unique(begin(subset), end(subset)),
    end(subset));
  return {
    mono_st(subset,
      [&](int u, int v) { return in_subtree(u, v); }),
    subset};
}
