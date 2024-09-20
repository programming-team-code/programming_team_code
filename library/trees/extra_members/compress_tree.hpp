#include "../../monotonic_stack/monotonic_stack.hpp"
//! https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/CompressTree.h
//! @code
//!   auto [par, orig_node] =
//!     lin_lca.compress_tree(subset);
//! @endcode
//! par[i] = parent of i in compressed tree, par[0]==-1
//! orig_node[i] = index of node in original tree
//! @time O(|subset| log |subset|)
//! @space O(|subset|)
array<vi, 2> compress_tree(vi subset) {
  auto cmp = [&](int u, int v) {
    return t[u].in < t[v].in;
  };
  sort(all(subset), cmp);
  int siz = sz(subset);
  rep(i, 1, siz)
    subset.push_back(lca(subset[i - 1], subset[i]));
  sort(all(subset), cmp);
  subset.erase(unique(all(subset)), end(subset));
  return {
    mono_st(subset,
      [&](int u, int v) { return in_subtree(u, v); }),
    subset};
}
