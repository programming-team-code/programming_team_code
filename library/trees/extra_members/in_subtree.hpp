//! returns 1 if v is in u's subtree
bool in_subtree(int u, int v) {
  return tin[u] <= tin[v] && tin[v] < tin[u] + siz[u];
}
