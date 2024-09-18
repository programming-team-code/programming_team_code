#pragma once
//! @param v node
//! @param c letter (don't subtract mn)
//! @returns child of v following edge with label c, -1 means
//! child doesn't exist
//! @time O(1)
//! @space O(1)
int get_child(int v, char c) {
  return v < sf_a.n - 1 ? adj[v][c - mn] : -1;
}
