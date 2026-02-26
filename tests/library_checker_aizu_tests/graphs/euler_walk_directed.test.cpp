#define PROBLEM \
  "https://judge.yosupo.jp/problem/eulerian_trail_directed"
#include "../template.hpp"
#include "../../../library/graphs/euler_walk.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int t;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;
    vector<vector<pii>> adj(n);
    vi deg(n);
    int s = -1;
    rep(i, 0, m) {
      int u, v;
      cin >> u >> v;
      s = u;
      adj[u].emplace_back(v, i);
      deg[u]++;
      deg[v]--;
    }
    if (*max_element(all(deg)) >= 2) {
      cout << "No" << '\n';
      continue;
    }
    if (ranges::count(deg, 1) >= 2) {
      cout << "No" << '\n';
      continue;
    }
    auto it = ranges::find(deg, 1);
    if (it != end(deg)) s = it - begin(deg);
    else if (s == -1) s = 0;
    vector<pii> res = euler_walk(adj, m, s);
    if (ssize(res) != m + 1) {
      cout << "No" << '\n';
      continue;
    }
    cout << "Yes" << '\n';
    rep(i, 0, sz(res)) cout << res[i].first << ' ';
    cout << '\n';
    rep(i, 1, sz(res)) cout << res[i].second << ' ';
    cout << '\n';
  }
  return 0;
}
