#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"
#include "../template.hpp"
#include "../mono_st_asserts.hpp"
#include "../../../library/data_structures_[l,r)/rmq.hpp"
int mn(int x, int y) { return min(x, y); }
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  mono_st_asserts(a);
  RMQ rmq(a, ranges::min);
  while (q--) {
    int l, r;
    cin >> l >> r;
    cout << rmq.query(l, r) << '\n';
  }
}
