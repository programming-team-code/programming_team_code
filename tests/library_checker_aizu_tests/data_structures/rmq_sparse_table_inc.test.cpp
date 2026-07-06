#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"
#include "../template.hpp"
#include "../../../library/data_structures_[l,r]/rmq.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vi a(n);
  rep(i, 0, n) cin >> a[i];
  RMQ rmq(a, ranges::min);
  while (q--) {
    int l, r;
    cin >> l >> r;
    cout << rmq.query(l, r - 1) << '\n';
  }
}
