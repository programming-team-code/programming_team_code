#define PROBLEM \
  "https://judge.yosupo.jp/problem/static_range_sum"
#include "../template.hpp"
#include "../../../library/data_structures_[l,r]/disjoint_rmq.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vector<ll> arr(n);
  rep(i, 0, n) cin >> arr[i];
  disjoint_rmq rmq(arr, plus<ll>{});
  while (q--) {
    int l, r;
    cin >> l >> r;
    cout << rmq.query(l, r - 1) << '\n';
  }
}
