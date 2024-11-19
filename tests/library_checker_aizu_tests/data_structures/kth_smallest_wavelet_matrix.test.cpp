#define PROBLEM \
  "https://judge.yosupo.jp/problem/range_kth_smallest"
#include "../template.hpp"
#include "../../../library/data_structures/seg_tree_uncommon/wavelet_matrix.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vector<ull> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    a[i] <<= 23;
  }
  wavelet_matrix wm(a, 1'000'000'000LL << 23);
  while (q--) {
    int l, r, k;
    cin >> l >> r >> k;
    cout << (wm.kth(l, r, k) >> 23) << '\n';
  }
  return 0;
}
