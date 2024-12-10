#define PROBLEM \
  "https://judge.yosupo.jp/problem/bipartitematching"
#undef _GLIBCXX_DEBUG
#undef _GLIBCXX_ASSERTIONS
#undef _GLIBCXX_SANITIZE_VECTOR
#undef _GLIBCXX_DEBUG_PEDANTIC

#include "../template.hpp"
#undef ll
#define ll int
#undef LLONG_MAX
#define LLONG_MAX 1'000'000'000
#include "../../../library/flow/dinic.hpp"
#include "../dinic_asserts.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int l, r, m;
  cin >> l >> r >> m;
  const int source = l + r;
  const int sink = l + r + 1;
  dinic d(l + r + 2);
  for (int i = 0; i < l; i++) d.add_edge(source, i, 1);
  for (int i = 0; i < r; i++) d.add_edge(i + l, sink, 1);
  vector<int> edge_ids(m);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    edge_ids[i] = d.add_edge(u, v + l, 1);
  }
  ll total_flow = d.calc(source, sink);
  cout << total_flow << '\n';
  // dinic_asserts(d, source, sink, total_flow);
  for (int i = 0; i < m; i++) {
    dinic::edge an_edge = d.edges[edge_ids[i]];
    if (an_edge.flow() == 1)
      cout << an_edge.v << ' ' << an_edge.to - l << '\n';
  }
  return 0;
}
