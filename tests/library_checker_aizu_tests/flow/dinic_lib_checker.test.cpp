#define PROBLEM \
  "https://judge.yosupo.jp/problem/bipartitematching"
#include "../template.hpp"
#include "../../../library/flow/dinic.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int l, r, m;
  cin >> l >> r >> m;
  const int source = l + r;
  const int sink = l + r + 1;
  dinic d(l + r + 2);
  for (int i = 0; i < l; i++) d.add_edge(source, i, 1);
  for (int i = 0; i < r; i++) d.add_edge(i + l, sink, 1);
  vector<int> u_node(m);
  vector<int> edge_ids(m);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u_node[i] = u;
    edge_ids[i] = d.add_edge(u, v + l, 1);
  }
  cout << d.calc(source, sink) << '\n';
  for (int i = 0; i < m; i++) {
    dinic::edge an_edge = d.edges[edge_ids[i]];
    if (an_edge.flow() == 1)
      cout << u_node[i] << ' ' << an_edge.to - l << '\n';
  }
  return 0;
}
