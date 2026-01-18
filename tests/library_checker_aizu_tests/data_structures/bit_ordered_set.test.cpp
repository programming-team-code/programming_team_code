#define PROBLEM \
  "https://judge.yosupo.jp/problem/ordered_set"
#include "../template.hpp"
#include "../../../library/data_structures_[l,r]/bit.hpp"
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
  BIT bit(ssize(compress));
  auto get_compressed_idx = [&](int val) -> int {
    int l = 0, r = ssize(compress);
    while (l + 1 < r) {
      int m = (l + r) / 2;
      if (compress[m] <= val) l = m;
      else r = m;
    }
    return l;
  };
  for (int i = 0; i < n; i++) {
    int val = get_compressed_idx(init[i]);
    bit.update(val, 1);
  }
  for (auto [type, x] : query) {
    if (type == 0) {
      x = get_compressed_idx(x);
      if (bit.query(x, x) == 0) bit.update(x, 1);
    } else if (type == 1) {
      x = get_compressed_idx(x);
      if (bit.query(x, x) == 1) bit.update(x, -1);
    } else if (type == 2) {
      int res = bit.walk(x);
      if (res == -1 || res == ssize(compress))
        cout << -1 << '\n';
      else cout << compress[res] << '\n';
    } else if (type == 3) {
      x = get_compressed_idx(x);
      cout << bit.query(x) << '\n';
    } else if (type == 4) {
      x = get_compressed_idx(x);
      int res = bit.walk(bit.query(x));
      if (res == -1) cout << -1 << '\n';
      else cout << compress[res] << '\n';
    } else {
      x = get_compressed_idx(x);
      int res = bit.walk(bit.query(x - 1) + 1);
      if (res == ssize(bit.s)) cout << -1 << '\n';
      else cout << compress[res] << '\n';
    }
  }
  return 0;
}
