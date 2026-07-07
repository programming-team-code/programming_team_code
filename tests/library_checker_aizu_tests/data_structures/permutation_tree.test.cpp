#define PROBLEM \
  "https://judge.yosupo.jp/problem/common_interval_decomposition_tree"
#include "../template.hpp"
#include "../perm_tree_asserts.hpp"
#include "../../../library/data_structures_[l,r)/uncommon/permutation_tree.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n;
  cin >> n;
  vi a(n);
  rep(i, 0, n) cin >> a[i];
  perm_tree pt = perm_tree_asserts(a);
  auto root = pt.root;
  auto ch = pt.ch;
  cout << sz(ch) << '\n';
  int curr_time = 0;
  vi node_to_time(sz(ch), -1);
  auto dfs = [&](this auto&& self, int u, int p) -> void {
    node_to_time[u] = curr_time++;
    cout << (p == -1 ? p : node_to_time[p]) << " "
         << pt.p[u].mn_idx << " "
         << pt.p[u].mn_idx + pt.p[u].len - 1 << " "
         << (pt.p[u].is_join || empty(ch[u]) ? "linear"
                                             : "prime")
         << '\n';
    for (int v : ch[u]) self(v, u);
  };
  dfs(root, -1);
  return 0;
}
