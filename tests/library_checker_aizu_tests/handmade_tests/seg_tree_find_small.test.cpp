#define PROBLEM                             \
  "https://judge.u-aizu.ac.jp/onlinejudge/" \
  "description.jsp?id=ITP1_1_A"
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
        int le = rnd(0, n - 1);
        int ri = rnd(le + 1, n);
        int diff = rnd(0, 10);
        seg.update(le, ri, diff);
        for (int i = le; i < ri; i++) a[i] += diff;
      } else {
        int le = rnd(0, n - 1);
        int ri = rnd(le + 1, n);
        int target_sum = rnd(0, 100);
        int smallest_index_greater_sum = ri;
        for (int pos = le, sum = 0; pos < ri; pos++) {
          sum += a[pos];
          if (sum > target_sum) {
            smallest_index_greater_sum = pos;
            break;
          }
        }
        int largest_index_greater_sum = le - 1;
        for (int pos = ri - 1, sum = 0; pos >= le; pos--) {
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
               seg.find_first(le, ri, f));
        st_walk_sum = 0;
        assert(largest_index_greater_sum ==
               seg.find_last(le, ri, f));
      }
    }
  }
  cout << "Hello World\n";
  return 0;
}
