#define PROBLEM                      \
  "https://judge.yosupo.jp/problem/" \
  "range_kth_smallest"
#include "../template.hpp"

#include "../../../library/data_structures/seg_tree_uncommon/kth_smallest_query.hpp"

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
    int start = 0, end = sz(sorted);
    while (start + 1 < end) {
      int mid = (start + end) / 2;
      if (sorted[mid] <= val) start = mid;
      else end = mid;
    }
    assert(sorted[start] == val);
    val = start - 50;
  }
  kth_smallest st(arr, -50, sz(sorted) - 50);
  for (int i = 0; i < n; i++) {
    int mx = arr[i];
    for (int j = i + 1; j <= min(i + 5, n); j++) {
      mx = max(mx, arr[j - 1]);
      assert(st.query(i, j, j - i) == mx);
    }
  }
  while (q--) {
    int l, r, k;
    cin >> l >> r >> k;
    cout << sorted[st.query(l, r, k + 1) + 50]
         << '\n';
  }
  return 0;
}
