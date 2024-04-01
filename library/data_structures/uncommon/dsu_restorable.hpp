/** @file */
#pragma once
/**
 * @see https://github.com/ucf-programming-team/hackpack-cpp /blob/master/content/data-structures/DSURestorable.h
 *
 * DSU without path compression, so non-amortized. Most operations are O(log n)
 */
struct dsu_restorable {
  int num_sets;
  vector<int> p;
  vector<ll> subtree;
  vector<optional<array<int, 3>>> st;
  dsu_restorable(int n) : num_sets(n), p(n, -1), subtree(n) {}
  inline int find(int u) {
    while (p[u] >= 0) u = p[u];
    return u;
  }
  bool join(int u, int v) {
    st.emplace_back();
    if ((u = find(u)) == (v = find(v))) return 0;
    if (p[u] > p[v]) swap(u, v);
    st.back() = {u, v, p[v]};
    p[u] += p[v], p[v] = u, subtree[u] += subtree[v], num_sets--;
    return 1;
  }
  void undo() {
    assert(!empty(st));
    if (st.back()) {
      auto [u, v, sz_v] = st.back().value();
      num_sets++, subtree[u] -= subtree[v], p[v] = sz_v, p[u] -= p[v];
    }
    st.pop_back();
  }
  inline int size(int u) { return -p[find(u)]; }
  inline bool same_set(int u, int v) { return find(u) == find(v); }
  inline ll sum(int u) { return subtree[find(u)]; }
  inline void add(int u, int d) {
    while (u >= 0) subtree[u] += d, u = p[u];
  }
};
