#define PROBLEM \
  "https://judge.yosupo.jp/problem/rooted_tree_isomorphism_classification"
// as std::map insert takes O(n) time in debug mode
#undef _GLIBCXX_DEBUG
#include "../template.hpp"
#include "../../../library/trees/uncommon/subtree_isomorphism.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n;
  cin >> n;
  vector<vector<int>> adj(n);
  for (int i = 1; i < n; i++) {
    int p;
    cin >> p;
    adj[p].push_back(i);
    adj[i].push_back(p);
  }
  auto [num_distinct_subtrees, iso_id] = subtree_iso(adj);
  cout << num_distinct_subtrees << '\n';
  for (int i = 0; i < n; i++) cout << iso_id[i] << " ";
  cout << '\n';
  return 0;
}
