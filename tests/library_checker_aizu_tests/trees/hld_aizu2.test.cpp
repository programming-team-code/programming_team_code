#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/problems/GRL_5_E"
#include "../template.hpp"
#include "../../../library/trees/hld.hpp"
#include "../../../library/data_structures/lazy_seg_tree.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n;
  cin >> n;
  vector<vector<int>> adj(n);
  for (int i = 0; i < n; i++) {
    int k;
    cin >> k;
    for (int j = 0; j < k; j++) {
      int v;
      cin >> v;
      assert(v != 0);
      adj[i].push_back(v);
      adj[v].push_back(i);
    }
  }
  HLD<1> hld(adj);
  seg_tree st(n);
  int q;
  cin >> q;
  while (q--) {
    int type;
    cin >> type;
    if (type == 0) {
      int v, x;
      cin >> v >> x;
      assert(v != 0);
      hld.path(0, v,
        [&](int l, int r) { st.update(l, r, x); });
    } else {
      assert(type == 1);
      int v;
      cin >> v;
      ll sum = 0;
      hld.path(0, v,
        [&](int l, int r) { sum += st.query(l, r); });
      cout << sum << '\n';
    }
  }
}
