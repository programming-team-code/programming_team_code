#define PROBLEM \
  "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"
#include "../../../library/data_structures/wavelet_merge/merge_sort_tree.hpp"
#define split split_2
#include "../../../library/data_structures/wavelet_merge/merge_sort_tree_updates.hpp"
#undef split
int main() {
  cin.tie(0)->sync_with_stdio(0);
  // brute force small cases
  for (int n = 0; n <= 25; n++) {
    for (int tests = 3; tests--;) {
      int minn = rnd<int>(-1000, 1000);
      int maxn = rnd<int>(-1000, 1000);
      if (minn > maxn) swap(minn, maxn);
      vector<int> arr(n);
      generate(begin(arr), end(arr),
        [&]() { return rnd<int>(minn, maxn); });
      merge_sort_tree mst(arr);
      merge_sort_tree_updates mstu(arr,
        vector<bool>(n, 1));
      for (int i = 0; i < n; i++) {
        assert(
          mst.kth_smallest(minn, maxn + 1, i + 1) == i);
        assert(
          mstu.kth_smallest(minn, maxn + 1, i + 1) == i);
      }
      for (int queries = 30; queries--;) {
        int x = rnd<int>(-1000, 1000);
        int y = rnd<int>(-1000, 1000);
        if (x > y) swap(x, y);
        for (int le = 0; le <= n; le++) {
          int cnt = 0;
          for (int ri = le; ri <= n; ri++) {
            assert(mst.rect_count(le, ri, x, y) == cnt);
            assert(mstu.rect_count(le, ri, x, y) == cnt);
            if (ri < n && x <= arr[ri] && arr[ri] < y)
              cnt++;
          }
        }
        vector<int> vals;
        for (int i = 0; i < n; i++)
          if (x <= arr[i] && arr[i] < y) vals.push_back(i);
        assert(sz(vals) == mst.rect_count(0, n, x, y));
        assert(sz(vals) == mstu.rect_count(0, n, x, y));
        for (int k = 1; k <= sz(vals); k++) {
          assert(mst.kth_smallest(x, y, k) == vals[k - 1]);
          assert(
            mstu.kth_smallest(x, y, k) == vals[k - 1]);
        }
      }
    }
  }
  cout << "Hello World\n";
  return 0;
}
