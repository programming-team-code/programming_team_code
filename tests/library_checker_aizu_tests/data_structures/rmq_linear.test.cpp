#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"
#include "../template.hpp"
#include "../../../library/data_structures/uncommon/linear_rmq.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  linear_rmq lin_rmq(a, less());
  while (q--) {
    int l, r;
    cin >> l >> r;
    int idx_min = lin_rmq.query_idx(l, r - 1);
    assert(l <= idx_min && idx_min < r);
    assert(lin_rmq.query(l, r - 1) == a[idx_min]);
    cout << a[idx_min] << '\n';
  }
}
