#define PROBLEM \
  "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"
#include "../../../library/data_structures_[l,r)/seg_tree_uncommon/merge_sort_tree.hpp"
#include "../../../library/data_structures_[l,r)/seg_tree_uncommon/wavelet_matrix.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  // brute force small cases
  for (int n = 0; n <= 25; n++) {
    for (int tests = 10; tests--;) {
      int minn = rnd<int>(-1000, 1000);
      int maxn = rnd<int>(-1000, 1000);
      if (minn > maxn) swap(minn, maxn);
      vector<int> arr(n);
      generate(begin(arr), end(arr),
        [&]() { return rnd<int>(minn, maxn); });
      merge_sort_tree mst(arr);
      vector<ll> arr_shifted(n);
      rep(i, 0, n) arr_shifted[i] = arr[i] - minn;
      wavelet_matrix wm(arr_shifted, 11);
      for (int queries = 30; queries--;) {
        int x = rnd<int>(minn, maxn);
        int y = rnd<int>(minn, maxn);
        if (x > y) swap(x, y);
        for (int l = 0; l <= n; l++) {
          int cnt = 0;
          for (int r = l; r <= n; r++) {
            assert(mst.query(l, r, x, y) == cnt);
            assert(wm.count(l, r, y - minn) -
                wm.count(l, r, x - minn) ==
              cnt);
            if (r < n && x <= arr[r] && arr[r] < y) cnt++;
          }
        }
      }
    }
  }
  cout << "Hello World\n";
  return 0;
}
