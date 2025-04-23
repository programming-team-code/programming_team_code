#pragma once
void edge_cd_asserts(const vector<vi>& adj, int cent, int split) {
  assert(0 < split && split < sz(adj[cent]));
  auto dfs = [&](auto&& self, int u, int p) -> int {
    int siz = 1;
    for (int v : adj[u])
      if (v != p) siz += self(self, v, u);
    return siz;
  };
  int sz_all = dfs(dfs, cent, -1);
  assert(sz_all >= 3);
  array<int, 2> cnts = {0, 0};
  array<int, 2> max_cnt = {0, 0};
  for (int i = 0; i < sz(adj[cent]); i++) {
    int sz_subtree = dfs(dfs, adj[cent][i], cent);
    assert(2 * sz_subtree <= sz_all);
    cnts[i < split] += sz_subtree;
    max_cnt[i < split] = max(max_cnt[i < split], sz_subtree);
  }
  assert(cnts[0] + cnts[1] + 1 == sz_all);

  if (sz_all == 4) return;

  // a is the number of edges in the smaller edge set
  // b is the number of edges in the larger edge set
  // so we know 1/2 <= b/(a+b)
  // returns true iff b/(a+b) <= 1/phi
  auto is_balanced = [&](ll a, ll b) -> bool {
    assert(a <= b);
    return b * b <= a * (a + b);
  };

  if (cnts[0] > cnts[1]) {
    swap(cnts[0], cnts[1]);
    swap(max_cnt[0], max_cnt[1]);
  }

  if (!is_balanced(cnts[0], cnts[1])) {
    int a = max_cnt[1];
    int b = cnts[1] - max_cnt[1];
    assert(a > 0);
    assert(b > 0);
    if (a > b) swap(a, b);
    assert(is_balanced(a, b));
  }
}
