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
  linear_rmq rmq_less_equal(a, less_equal());
  vector<int> neg_a(n);
  for (int i = 0; i < n; i++) neg_a[i] = -a[i];
  linear_rmq rmq_greater(neg_a, greater());
  linear_rmq rmq_greater_equal(neg_a, greater_equal());
  while (q--) {
    int l, r;
    cin >> l >> r;
    int idx_right_min = rmq_less.idx(l, r - 1);
    assert(idx_right_min + 1 == r ||
      rmq_less.query(idx_right_min + 1, r - 1) >
        a[idx_right_min]);
    assert(l <= idx_right_min && idx_right_min < r);
    assert(rmq_less.query(l, r - 1) == a[idx_right_min]);
    assert(idx_right_min == rmq_greater.idx(l, r - 1));
    int idx_left_min = rmq_less_equal.idx(l, r - 1);
    assert(l == idx_left_min ||
      rmq_less_equal.query(l, idx_left_min - 1) >
        a[idx_left_min]);
    assert(l <= idx_left_min && idx_left_min < r);
    assert(
      idx_left_min == rmq_greater_equal.idx(l, r - 1));
    assert(a[idx_right_min] == a[idx_left_min]);
    assert(idx_left_min <= idx_right_min);
    cout << a[idx_right_min] << '\n';
  }
}
