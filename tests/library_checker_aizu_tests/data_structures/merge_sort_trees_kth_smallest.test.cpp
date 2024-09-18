#define PROBLEM \
  "https://judge.yosupo.jp/problem/range_kth_smallest"
// since this causes an O(n) partition check for each call to
// `lower_bound`, causing TLE.
#undef _GLIBCXX_DEBUG
#include "../template.hpp"
#include "../../../library/data_structures/wavelet_merge/merge_sort_tree.hpp"
#define split split_2
#include "../../../library/data_structures/wavelet_merge/merge_sort_tree_updates.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vector<int> arr(n);
  for (int i = 0; i < n; i++) cin >> arr[i];
  vector<int> sorted(arr);
  sort(begin(sorted), end(sorted));
  vector<int> inverted(n);
  map<int, int> ptr;
  for (int i = 0; i < n; i++) {
    int pos =
      int(lower_bound(begin(sorted), end(sorted), arr[i]) -
        begin(sorted));
    if (!ptr.count(arr[i])) ptr[arr[i]] = pos;
    inverted[ptr[arr[i]]++] = i;
  }
  merge_sort_tree mst(inverted);
  merge_sort_tree_updates mstu(inverted, vector<bool>(n, 1));
  while (q--) {
    int le, ri, k;
    cin >> le >> ri >> k;
    int res = mst.kth_smallest(le, ri, k + 1);
    assert(res == mstu.kth_smallest(le, ri, k + 1));
    cout << sorted[res] << '\n';
  }
  return 0;
}
