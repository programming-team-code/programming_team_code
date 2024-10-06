//! returns 1 if w is on path from u to v
bool on_path(int u, int v, int w) {
  return (in_subtree(w, u) || in_subtree(w, v)) &&
    in_subtree(lca(u, v), w);
}
