/**
 * @param v node
 * @returns range [le, ri) such that the following (ri - le) substrings are equal:
 *     - for all i in [le, ri): s.substr(sa[i], lcp_len(v))
 * @time O(1)
 * @space O(1)
 */
pair<int, int> sa_range(int v) {
  if (v < sf_a.n - 1) return {le[v] + 1, ri[v] + 1};
  return {v - sf_a.n + 1, v - sf_a.n + 2};
}
/**
 * @param v node
 * @returns length of longest common prefix of v's interval/range
 * @time O(1)
 * @space O(1)
 */
int len_lcp_range(int v) {
  return v < sf_a.n - 1 ? sf_a.lcp[v] : sf_a.n - sf_a.sa[v - sf_a.n + 1];
}
/**
 * @param v node
 * @param c letter (don't subtract mn)
 * @returns child of v following edge with label c, -1 means child doesn't exist
 * @time O(1)
 * @space O(1)
 */
int get_child(int v, char c) {
  return v < sf_a.n - 1 ? adj[v][c - mn] : -1;
}
/**
 * performs trie-style downwards tree walk
 * @param t needle
 * @returns range [le, ri) such that:
 *     - for all i in [le, ri): t == s.substr(sa[i], sz(t))
 *     - `ri - le` is the # of matches of t in s.
 * @time O(|t|)
 * @space O(1)
 */
pair<int, int> find_str(const string& t) {
  int v = root;
  for (int i = 0; i < ((int)size(t)); i++) {
    if (i == len_lcp_range(v)) {
      v = get_child(v, t[i]);
      if (v == -1) return {0, 0};
    }
    int sa_le = sa_range(v).first;
    if (sf_a.s[sf_a.sa[sa_le] + i] != t[i]) return {0, 0};
  }
  return sa_range(v);
}
