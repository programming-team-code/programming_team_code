#pragma once
//! @see https://github.com/ucf-programming-team/hackpack-cpp/blob/master/content/data-structures/DSURestorable.h
//! DSU without path compression, so non-amortized. Most operations are O(log n)
struct dsu_restorable {
  int num_sets;
  vi p;
  vector<ll> subtree;
  vector<optional<array<int, 3>>> st;
  dsu_restorable(int n): num_sets(n), p(n, -1), subtree(n) {}
  int find(int v) {
    while (p[v] >= 0) v = p[v];
    return v;
  }
  bool join(int u, int v) {
    st.emplace_back();
    if ((u = find(u)) == (v = find(v))) return 0;
    if (p[u] > p[v]) swap(u, v);
    st.back() = {u, v, p[v]};
    p[u] += p[v], p[v] = u, subtree[u] += subtree[v],
                  num_sets--;
    return 1;
  }
  void undo() {
    if (st.back()) {
      auto [u, v, sz_v] = st.back().value();
      num_sets++, subtree[u] -= subtree[v], p[v] = sz_v,
                                            p[u] -= p[v];
    }
    st.pop_back();
  }
  int size(int v) { return -p[find(v)]; }
  bool same_set(int u, int v) { return find(u) == find(v); }
  ll sum(int v) { return subtree[find(v)]; }
  void add(int v, int d) {
    while (v >= 0) subtree[v] += d, v = p[v];
  }
};
