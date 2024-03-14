#define PROBLEM "https://judge.yosupo.jp/problem/static_range_sum"
#include "../template.hpp"

#include "../../../library/data_structures/uncommon/disjoint_rmq.hpp"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vector<int64_t> arr(n);
  for (int i = 0; i < n; i++)
    cin >> arr[i];
  disjoint_rmq rmq(arr, plus<int64_t>{});
  while (q--) {
    int l, r;
    cin >> l >> r;
    cout << rmq.query(l, r) << '\n';
  }
}
