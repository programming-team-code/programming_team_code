#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/problems/GRL_3_A"
#include "../template.hpp"
#include "../../../library/graphs/bcc_callback.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, m;
  cin >> n >> m;
  vector<basic_string<int>> adj(n);
  for (int i = 0; i < n; i++) adj[i] += i;
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    adj[u] += v;
    adj[v] += u;
  }
  vi cnt(n);
  bcc_callback(adj, [&](const vi& nodes) {
    assert(sz(nodes) >= 2);
    for (int v : nodes) cnt[v]++;
  });
  rep(i, 0, n) if (cnt[i] >= 2) cout << i << '\n';
  return 0;
}
