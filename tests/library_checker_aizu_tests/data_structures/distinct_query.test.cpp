#define PROBLEM \
  "https://judge.yosupo.jp/problem/static_range_count_distinct"
#include "../template.hpp"
#include "../../../library/data_structures/seg_tree_uncommon/distinct_query.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  distinct_query dq(a);
  while (q--) {
    int l, r;
    cin >> l >> r;
    cout << dq.query(l, r) << '\n';
  }
  return 0;
}
