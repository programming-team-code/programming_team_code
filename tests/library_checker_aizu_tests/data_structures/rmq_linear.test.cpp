#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"
#include "../template.hpp"
#include "../../../library/data_structures_[l,r]/linear_rmq.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  linear_rmq rmq_less(a, less());
  while (q--) {
    int l, r;
    cin >> l >> r;
    int idx_right_min = rmq_less.idx(l, r - 1);
    assert(idx_right_min + 1 == r ||
           rmq_less.query(idx_right_min + 1, r - 1) >
             a[idx_right_min]);
    assert(l <= idx_right_min && idx_right_min < r);
    assert(rmq_less.query(l, r - 1) == a[idx_right_min]);
    cout << a[idx_right_min] << '\n';
  }
}
