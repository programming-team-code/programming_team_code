#define PROBLEM \
  "https://judge.yosupo.jp/problem/bipartitematching"
#include "../template.hpp"
#include "../../../library/graphs/hopcroft_karp.hpp"
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
  hopcroft_karp res(adj, r);
  cout << res.m_sz << '\n';
  // asserting correctness of both to_r, and to_l (as
  // well as printing answer)
  int size_l = 0;
  for (int i = 0; i < l; i++) {
    if (res.to_r[i] != -1) {
      size_l++;
      int node_r = res.to_r[i];
      cout << i << " " << node_r << '\n';
      assert(res.to_l[node_r] == i);
    }
  }
  int size_r = 0;
  for (int i = 0; i < r; i++) {
    if (res.to_l[i] != -1) {
      size_r++;
      int node_l = res.to_l[i];
      assert(res.to_r[node_l] == i);
    }
  }
  assert(size_l == res.m_sz);
  assert(size_r == res.m_sz);
  // asserting found min vertex cover is correct
  int cnt =
    accumulate(begin(res.mvc_l), end(res.mvc_l), 0) +
    accumulate(begin(res.mvc_r), end(res.mvc_r), 0);
  assert(cnt == res.m_sz); // size of min vertex cover
                           // == size of max matching
  for (auto [u, v] : edges)
    assert(res.mvc_l[u] || res.mvc_r[v]);
  return 0;
}
