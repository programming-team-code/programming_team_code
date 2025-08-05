//! returns 1 if v is in u's subtree
bool in_subtree(int u, int v) {
  return in[u] <= in[v] && in[v] < in[u] + siz[u];
}
