#define PROBLEM \
  "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_7_A"
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
  int size_matching = hopcroftKarp(adj, ri);
  auto [mvc_l, mvc_r] = cover(adj, ri);
  int size_r = 0;
  for (int i = 0; i < r; i++)
    if (ri[i] != -1) size_r++;
  assert(size_r == size_matching);
  // asserting found min vertex cover is correct
  int cnt = accumulate(begin(mvc_l), end(mvc_l), 0) +
            accumulate(begin(mvc_r), end(mvc_r), 0);
  assert(cnt == size_matching);
  for (auto [u, v] : edges) assert(mvc_l[u] || mvc_r[v]);
  cout << size_matching << '\n';
  return 0;
}
