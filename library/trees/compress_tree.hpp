//! @see https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/CompressTree.h
//! Given a rooted tree and a subset S of nodes, compute the minimal subtree
//! that contains all the nodes by adding all (at most |S|-1) pairwise LCA's and
//! compressing edges.
//!
//! @code{.cpp}
//!     auto [par, orig_node] = lin_lca.compress_tree(subset);
//! @endcode
//!
//! @param subset subset of nodes
//! @returns vectors `par`, `orig_node`, for node i in compressed tree:
//!          par[i] = parent of i in compressed tree; par[0] == -1; par[i] < i
//!          orig_node[i] = corresponding node in big tree
//! @time O(k log k); k = sz(subset)
//! @space O(k) vectors are allocated and returned
array<vi, 2> compress_tree(vi subset) {
  auto cmp = [&](int u, int v) { return t[u].in < t[v].in; };
  sort(all(subset), cmp);
  int siz = sz(subset);
  rep(i, 1, siz)
    subset.push_back(lca(subset[i - 1], subset[i]));
  sort(all(subset), cmp);
  subset.erase(unique(all(subset)), end(subset));
  return {mono_st(subset,
            [&](int u, int v) { return in_subtree(u, v); }),
    subset};
}
