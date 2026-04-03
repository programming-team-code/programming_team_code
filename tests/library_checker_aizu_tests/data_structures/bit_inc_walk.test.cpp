#define PROBLEM \
  "https://judge.yosupo.jp/problem/predecessor_problem"
#include "../template.hpp"
#include "../../../library/data_structures_[l,r]/bit.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  string s;
  cin >> n >> q >> s;
  vector<ll> init(n);
  for (int i = 0; i < n; i++) init[i] = s[i] - '0';
  BIT bit(init);
  while (q--) {
    int type, k;
    cin >> type >> k;
    if (type == 0) {
      if (bit.query(k, k) == 0) bit.update(k, 1);
    } else if (type == 1) {
      if (bit.query(k, k) == 1) bit.update(k, -1);
    } else if (type == 2) {
      cout << bit.query(k, k) << '\n';
    } else if (type == 3) {
      if (bit.query(k, n - 1) == 0) cout << -1 << '\n';
      else {
        ll order = bit.query(k - 1);
        int res = -1;
        bit.walk([&](int r, ll sum) {
          if (sum <= order) return 1;
          res = r;
          return 0;
        });
        cout << res << '\n';
      }
    } else {
      if (bit.query(k) == 0) cout << -1 << '\n';
      else {
        ll order = bit.query(k);
        int res = -1;
        bit.walk([&](int r, ll sum) {
          if (sum >= order) {
            res = r;
            return 0;
          }
          return 1;
        });
        cout << res << '\n';
      }
    }
  }
  return 0;
}
