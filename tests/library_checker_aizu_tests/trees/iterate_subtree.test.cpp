#define PROBLEM "https://judge.yosupo.jp/problem/lca"
#include "../template.hpp"

#include "../../../library/trees/lca_rmq/lca_rmq.hpp"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vector<vector<int>> adj(n);
  for (int i = 1; i < n; i++) {
    int par;
    cin >> par;
    adj[par].push_back(i);
  }
  LCA lc(adj);
  {
    vector<int> cnt_small_iterated(n), cnt_big_iterated(n);
    for (int i = 0; i < n; i++) {
      if (empty(adj[i])) continue;
      int big_ch_idx = int(max_element(begin(adj[i]), end(adj[i]), [&](int x, int y) { return lc.t[x].sub_sz < lc.t[y].sub_sz; }) - begin(adj[i]));
      for (int j = 0; j < sz(adj[i]); j++) {
        int u = adj[i][j];
        assert(lc.t[u].sub_sz <= lc.t[adj[i][big_ch_idx]].sub_sz);
        if (j == big_ch_idx) {
          int le = lc.t[u].in;
          int ri = lc.t[u].in + lc.t[u].sub_sz;
          cnt_big_iterated[le]++;
          if (ri < n) cnt_big_iterated[ri]--;
          continue;
        }
#include "../../../library/trees/lca_rmq/iterate_subtree.hpp"
        assert(lc.t[u].d <= lc.t[v].d);
        assert(lc.in_subtree(u, v));
        cnt_small_iterated[v]++;
      }
    }
  }
  partial_sum(begin(cnt_big_iterated), end(cnt_big_iterated), begin(cnt_big_iterated));
  for (int i = 0; i < n; i++) {
    // at each merge (small to large), subtree size doubles or more
    // how many doubles until it reaches n?
    // sub_sz * 2^k ~= n
    // 2^k ~= n / sub_sz
    // k ~= __lg(n / sub_sz)
    assert(cnt_small_iterated[i] <= __lg(n / lc.t[i].sub_sz));
    assert(cnt_small_iterated[i] + cnt_big_iterated[lc.t[i].in] == lc.t[i].d);
  }
}
while (q--) {
  int u, v;
  cin >> u >> v;
  cout << lc.lca(u, v) << '\n';
}
}
