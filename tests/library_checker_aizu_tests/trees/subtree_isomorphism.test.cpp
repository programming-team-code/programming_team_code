#define PROBLEM "https://judge.yosupo.jp/problem/rooted_tree_isomorphism_classification"
#include "../template.hpp"

#include "../../../library/trees/subtree_isomorphism.hpp"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n;
  cin >> n;
  vector<vector<int>> adj_unrooted(2 * n);
  vector<vector<int>> adj_rooted(n);
  for (int i = 1; i < n; i++) {
    int p;
    cin >> p;
    adj_unrooted[p].push_back(i);
    adj_unrooted[i].push_back(p);
    adj_unrooted[p + n].push_back(i + n);
    adj_unrooted[i + n].push_back(p + n);
    adj_rooted[p].push_back(i);
  }
  auto [num_distinct_subtrees, iso_id] = subtree_iso(adj_unrooted);
  auto [num_distinct_subtrees_rooted, iso_id_rooted] = subtree_iso(adj_rooted);
  assert(num_distinct_subtrees == num_distinct_subtrees_rooted);
  cout << num_distinct_subtrees << '\n';
  for (int i = 0; i < n; i++) {
    cout << iso_id[i] << " ";
    assert(iso_id[i] == iso_id_rooted[i]);
    assert(iso_id[i] == iso_id[i + n]);
  }
  cout << '\n';
  return 0;
}
