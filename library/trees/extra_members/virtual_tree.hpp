//! https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/CompressTree.h
//! @code
//!   vector<vi> adj(n);
//!   LCA lca(adj);
//!   auto [par, orig_node] =
//!     lca.compress_tree(subset);
//! @endcode
//! par[i] = parent of i in compressed tree, par[0]==-1
//! orig_node[i] = index of node in original tree
//! @time O(|subset| log |subset|)
//! @space O(|subset|)
array<vi, 2> compress_tree(vi subset) {
  auto proj = [&](int v) { return tin[v]; };
  ranges::sort(subset, {}, proj);
  int len = sz(subset);
  rep(i, 1, len)
    subset.push_back(lca(subset[i - 1], subset[i]));
  ranges::sort(subset, {}, proj);
  subset.erase(unique(all(subset)), end(subset));
  return {
    mono_st(subset,
      [&](int u, int v) { return in_subtree(u, v); }),
    subset};
}
