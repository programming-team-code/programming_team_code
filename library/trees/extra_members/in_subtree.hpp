//! returns true if v is in u's subtree
bool in_subtree(int u, int v) {
  return t[u].in <= t[v].in &&
    t[v].in < t[u].in + t[u].sub_sz;
}
