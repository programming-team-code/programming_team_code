#define PROBLEM \
  "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"
#include "../../../library/data_structures/lazy_seg_tree.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  for (int iters = 0; iters < 100; ++iters) {
    int n = 1'000;
    seg_tree seg(n);
    vector<int> a(n);
    for (int q = 0; q < 1'000; q++) {
      if (rnd(0, 1) == 0) {
        int l = rnd(0, n - 1);
        int r = rnd(l + 1, n);
        int diff = rnd(0, 10);
        seg.update(l, r, diff);
        for (int i = l; i < r; i++) a[i] += diff;
      } else {
        int l = rnd(0, n - 1);
        int r = rnd(l + 1, n);
        int target_sum = rnd(0, 100);
        int smallest_index_greater_sum = r;
        for (int pos = l, sum = 0; pos < r; pos++) {
          sum += a[pos];
          if (sum > target_sum) {
            smallest_index_greater_sum = pos;
            break;
          }
        }
        int largest_index_greater_sum = l - 1;
        for (int pos = r - 1, sum = 0; pos >= l; pos--) {
          sum += a[pos];
          if (sum > target_sum) {
            largest_index_greater_sum = pos;
            break;
          }
        }
        int st_walk_sum;
        auto f = [&](int64_t x, int, int) -> bool {
          if (st_walk_sum + x <= target_sum) {
            st_walk_sum += x;
            return 0;
          }
          return 1;
        };
        st_walk_sum = 0;
        assert(smallest_index_greater_sum ==
          seg.find_first(l, r, f));
        st_walk_sum = 0;
        assert(largest_index_greater_sum ==
          seg.find_last(l, r, f));
      }
    }
  }
  cout << "Hello World\n";
  return 0;
}
