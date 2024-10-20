#define PROBLEM \
  "https://judge.yosupo.jp/problem/static_range_frequency"
#include "../template.hpp"
#include "../../../library/data_structures/wavelet_merge/wavelet_tree.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vector<int> arr(n);
  for (int i = 0; i < n; i++) cin >> arr[i];
  vector<int> sorted(arr);
  sort(begin(sorted), end(sorted));
  sorted.erase(unique(begin(sorted), end(sorted)),
    end(sorted));
  for (int& val : arr) {
    int l = 0, r = sz(sorted);
    while (r - l > 1) {
      int mi = l + (r - l) / 2;
      if (sorted[mi] <= val) l = mi;
      else r = mi;
    }
    assert(l < sz(arr) && sorted[l] == val);
    val = l - 30;
  }
  wavelet_tree wt(arr, -30, sz(sorted) - 30);
  while (q--) {
    int l, r, x;
    cin >> l >> r >> x;
    int start = 0, end = sz(sorted);
    while (end - start > 1) {
      int mi = start + (end - start) / 2;
      if (sorted[mi] <= x) start = mi;
      else end = mi;
    }
    if (start == sz(sorted) || sorted[start] != x)
      cout << 0 << '\n';
    else {
      int idx = start - 30;
      assert(wt.rect_count(l, r, idx, idx) == 0);
      cout << wt.rect_count(l, r, idx, idx + 1) << '\n';
    }
  }
  return 0;
}
