#define PROBLEM \
  "https://judge.yosupo.jp/problem/ordered_set"
#include "../template.hpp"
#include "../../../library/data_structures/bit_inc.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vector<int> init(n);
  for (int i = 0; i < n; i++) cin >> init[i];
  vector<int> compress(init);
  vector<array<int, 2>> query(q);
  for (int i = 0; i < q; i++) {
    int type, x;
    cin >> type >> x;
    query[i] = {type, x};
    compress.push_back(x);
  }
  ranges::sort(compress);
  compress.erase(unique(all(compress)), end(compress));
  bit_inc bit(ssize(compress));
  for (int i = 0; i < n; i++) {
    int val = ranges::lower_bound(compress, init[i]) -
      begin(compress);
    bit.update(val, 1);
  }
  for (auto [type, x] : query) {
    if (type == 0) {
      x =
        ranges::lower_bound(compress, x) - begin(compress);
      if (bit.query(x, x) == 0) bit.update(x, 1);
    } else if (type == 1) {
      x =
        ranges::lower_bound(compress, x) - begin(compress);
      if (bit.query(x, x) == 1) bit.update(x, -1);
    } else if (type == 2) {
      int res = bit.walk(x);
      if (res == -1 || res == ssize(compress))
        cout << -1 << '\n';
      else cout << compress[res] << '\n';
    } else if (type == 3) {
      x =
        ranges::lower_bound(compress, x) - begin(compress);
      cout << bit.query(x) << '\n';
    } else if (type == 4) {
      x =
        ranges::lower_bound(compress, x) - begin(compress);
      int res = bit.prev(x);
      if (res == -1) cout << -1 << '\n';
      else cout << compress[res] << '\n';
    } else {
      x =
        ranges::lower_bound(compress, x) - begin(compress);
      int res = bit.next(x);
      if (res == ssize(bit.s)) cout << -1 << '\n';
      else cout << compress[res] << '\n';
    }
  }
  return 0;
}
