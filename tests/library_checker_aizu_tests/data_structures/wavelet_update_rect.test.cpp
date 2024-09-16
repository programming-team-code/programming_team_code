#define PROBLEM \
  "https://judge.yosupo.jp/problem/static_range_frequency"
#include "../template.hpp"

#include "../../../library/data_structures/wavelet_merge/wavelet_tree_updates.hpp"

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
    int le = 0, ri = sz(sorted);
    while (ri - le > 1) {
      int mi = le + (ri - le) / 2;
      if (sorted[mi] <= val) le = mi;
      else ri = mi;
    }
    assert(le < sz(arr) && sorted[le] == val);
    val = le - 30;
  }
  wavelet_tree_updates wtu(arr, -30,
                           max(1, int(sz(sorted))) - 30,
                           vector<bool>(n, 1));
  while (q--) {
    int le, ri, x;
    cin >> le >> ri >> x;
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
      assert(wtu.rect_count(le, ri, idx, idx) == 0);
      cout << wtu.rect_count(le, ri, idx, idx + 1) << '\n';
    }
  }
  return 0;
}
