#define PROBLEM \
  "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"
#include "../../../library/data_structures/wavelet_merge/wavelet_tree.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  // brute force small cases
  for (int n = 0; n <= 65; n++) {
    for (int tests = 3; tests--;) {
      int minn = rnd<int>(-1000, 1000);
      int maxn = rnd<int>(-1000, 1000);
      if (minn > maxn) swap(minn, maxn);
      vector<int> arr(n);
      generate(begin(arr), end(arr),
        [&]() { return rnd<int>(minn, maxn); });
      wavelet_tree wt(arr, minn, maxn + 1);
      for (int queries = 3; queries--;) {
        int x = rnd<int>(-1000, 1000);
        int y = rnd<int>(-1000, 1000);
        if (x > y) swap(x, y);
        for (int le = 0; le <= n; le++) {
          int cnt = 0, sum = 0;
          for (int ri = le; ri <= n; ri++) {
            assert(wt.rect_count(le, ri, x, y) == cnt);
            assert(wt.rect_sum(le, ri, x, y) == sum);
            if (ri < n && x <= arr[ri] && arr[ri] < y) {
              cnt++;
              sum += arr[ri];
            }
          }
        }
      }
      if (n <= 35) {
        for (int le = 0; le <= n; le++) {
          for (int ri = le; ri <= n; ri++) {
            vector<int> subarray(begin(arr) + le,
              begin(arr) + ri);
            sort(begin(subarray), end(subarray));
            int sum = 0;
            for (int k = 0; k <= sz(subarray); k++) {
              if (k) {
                assert(wt.kth_smallest(le, ri, k) ==
                  subarray[k - 1]);
                sum += subarray[k - 1];
              }
              assert(wt.kth_sum(le, ri, k) == sum);
            }
          }
        }
      }
    }
  }
  // max test for overflow
  {
    const int mx_n = 100'000, large = 1'000'000'000,
              val_range = 20;
    vector<int> arr(mx_n), count_val(val_range);
    for (int& val : arr) {
      val = rnd<int>(large, large + val_range - 1);
      count_val[val - large]++;
    }
    wavelet_tree wt(arr, large, large + val_range);
    for (int x = large; x <= large + val_range; x++) {
      int cnt = 0;
      int64_t sum = 0;
      for (int y = x; y <= large + val_range; y++) {
        assert(wt.rect_count(0, mx_n, x, y) == cnt);
        assert(wt.rect_sum(0, mx_n, x, y) == sum);
        if (y < large + val_range) {
          cnt += count_val[y - large];
          sum += 1LL * y * count_val[y - large];
        }
      }
    }
    for (int tests_kth_sum = 100; tests_kth_sum--;) {
      int k = rnd<int>(0, mx_n);
      if (tests_kth_sum == 50) k = 0;
      if (tests_kth_sum == 49) k = mx_n;
      if (k == 0) {
        assert(wt.kth_sum(0, mx_n, k) == 0);
        continue;
      }
      int curr_cnt = 0;
      int64_t curr_sum = 0;
      int kth_smallest_naive = -1;
      for (int i = 0; i < val_range; i++) {
        if (curr_cnt + count_val[i] >= k) {
          kth_smallest_naive = i + large;
          curr_sum += 1LL * (i + large) * (k - curr_cnt);
          break;
        }
        curr_cnt += count_val[i];
        curr_sum += 1LL * (i + large) * count_val[i];
      }
      assert(kth_smallest_naive != -1);
      assert(
        wt.kth_smallest(0, mx_n, k) == kth_smallest_naive);
      assert(wt.kth_sum(0, mx_n, k) == curr_sum);
    }
  }
  cout << "Hello World\n";
  return 0;
}
