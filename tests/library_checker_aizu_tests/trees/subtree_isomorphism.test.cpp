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
  vector<vi> adj(n);
  rep(i, 1, n) {
    int p;
    cin >> p;
    adj[p].push_back(i);
    adj[i].push_back(p);
  }
  auto [num_distinct_subtrees, iso_id] = subtree_iso(adj);
  cout << num_distinct_subtrees << '\n';
  rep(i, 0, n) cout << iso_id[i] << " ";
  cout << '\n';
  return 0;
}
