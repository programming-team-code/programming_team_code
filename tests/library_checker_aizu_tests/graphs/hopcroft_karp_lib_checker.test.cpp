#define PROBLEM \
  "https://judge.yosupo.jp/problem/bipartitematching"
#include "../template.hpp"
#include "../../../library/graphs/min_vertex_cover.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int l, r, m;
  cin >> l >> r >> m;
  vector<vector<int>> adj(l);
  vector<pair<int, int>> edges;
  while (m--) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    edges.emplace_back(u, v);
  }
  vi ri(r, -1);
  int m_sz = hopcroftKarp(adj, ri);
  auto [mvc_l, mvc_r] = cover(adj, ri);
  cout << m_sz << '\n';
  int size_r = 0;
  for (int i = 0; i < r; i++) {
    if (ri[i] != -1) {
      size_r++;
      cout << ri[i] << ' ' << i << '\n';
    }
  }
  assert(size_r == m_sz);
  int cnt = accumulate(begin(mvc_l), end(mvc_l), 0) +
            accumulate(begin(mvc_r), end(mvc_r), 0);
  assert(cnt == m_sz);
  for (auto [u, v] : edges) assert(mvc_l[u] || mvc_r[v]);
  return 0;
}
