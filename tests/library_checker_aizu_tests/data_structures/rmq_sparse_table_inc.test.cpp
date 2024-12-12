#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"
#include "../template.hpp"
#include "../../../library/data_structures/rmq_inc.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  rmq_inc rmq(a, ranges::min);
  while (q--) {
    int l, r;
    cin >> l >> r;
    cout << rmq.query(l, r - 1) << '\n';
  }
}
