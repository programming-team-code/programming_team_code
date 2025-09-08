/**
 * Author: Lukas Polacek
 * Date: 2009-10-26
 * License: CC0
 * Source: folklore
 * Description: Disjoint-set data structure.
 * Time: $O(\alpha(N))$
 */
struct UF {
  vector<int> e;
  UF(int n): e(n, -1) {}
  bool sameSet(int a, int b) { return find(a) == find(b); }
  int size(int x) { return -e[find(x)]; }
  int find(int x) {
    return e[x] < 0 ? x : e[x] = find(e[x]);
  }
  bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (e[a] > e[b]) swap(a, b);
    e[a] += e[b];
    e[b] = a;
    return true;
  }
};
//! Given triplets (l1,l2,len); joins (l1,l2),
//!   (l1+1,l2+1), ..., (l1+len-1,l2+len-1)
//! @time O((n + q) * \alpha(n))
//! @space O(n + q)
UF get_rp_dsu(const vector<array<int, 3>>& rests, int n) {
  vector<vector<pair<int, int>>> rests_by_len(n + 1);
  for (auto [l1, l2, len] : rests)
    rests_by_len[len].emplace_back(l1, l2);
  UF uf(n);
  for (int len = n; len > 0; len--)
    for (auto [l1, l2] : rests_by_len[len])
      if (uf.join(l1, l2))
        rests_by_len[len - 1].emplace_back(l1 + 1, l2 + 1);
  return uf;
}
