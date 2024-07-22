/** @file */
#pragma once
/**
 * @param u node
 * @param c letter (don't subtract mn)
 * @returns child of u following edge with label c, -1 means child doesn't exist
 * @time O(1)
 * @space O(1)
 */
int get_child(int u, char c) {
  return u < sf_a.n - 1 ? adj[u][c - mn] : -1;
}
