/**
 * @param u node
 * @returns range [le, ri) such that the following (ri - le) substrings are equal:
 *     - for all i in [le, ri): s.substr(sa[i], lcp_len(u))
 * @time O(1)
 * @space O(1)
 */
inline array<int, 2> sa_range(int u) {
  if (u < sf_a.n - 1) return {le[u] + 1, ri[u] + 1};
  return {u - sf_a.n + 1, u - sf_a.n + 2};
}
/**
 * @param u node
 * @returns length of longest common prefix of u's interval/range
 * @time O(1)
 * @space O(1)
 */
inline int len_lcp_range(int u) {
  return u < sf_a.n - 1 ? sf_a.lcp[u] : sf_a.n - sf_a.sa[u - sf_a.n + 1];
}
/**
 * @param u node
 * @param c letter (don't subtract mn)
 * @returns child of u following edge with label c, -1 means child doesn't exist
 * @time O(1)
 * @space O(1)
 */
inline int get_child(int u, char c) {
  return u < sf_a.n - 1 ? adj[u][c - mn] : -1;
}
/**
 * performs trie-style downwards tree walk
 * @param t needle
 * @returns range [le, ri) such that:
 *     - for all i in [le, ri): t == s.substr(sa[i], ssize(t))
 *     - `ri - le` is the # of matches of t in s.
 * @time O(|t|)
 * @space O(1)
 */
array<int, 2> find_str(const string& t) {
  int u = root;
  for (int i = 0; i < ssize(t); i++) {
    if (i == len_lcp_range(u)) {
      u = get_child(u, t[i]);
      if (u == -1) return {0, 0};
    }
    int sa_le = sa_range(u)[0];
    if (sf_a.s[sf_a.sa[sa_le] + i] != t[i]) return {0, 0};
  }
  return sa_range(u);
}
