#define PROBLEM \
  "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"
#include "../../../library/data_structures_[l,r)/rmq.hpp"
#include "../../../library/data_structures_[l,r]/linear_rmq.hpp"
void test_all_subarrays(const vi& a) {
  auto n = sz(a);
  RMQ rmq(a, [](auto x, auto y) { return min(x, y); });
  linear_rmq lin_rmq(a, less());
  rep(l, 0, n) {
    for (int r = l + 1; r <= n; r++) {
      int idx_min = lin_rmq.idx(l, r - 1);
      assert(l <= idx_min && idx_min < r);
      assert(a[idx_min] == rmq.query(l, r));
    }
  }
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  for (int n = 1; n <= 8; n++) {
    vi perm(n);
    ranges::iota(perm, 0);
    do {
      test_all_subarrays(perm);
    } while (ranges::next_permutation(perm).found);
  }
  for (int n = 1; n <= 100; n++) {
    rep(times, 0, 40) {
      vi a(n);
      rep(i, 0, n) a[i] = rnd<int>(INT_MIN, INT_MAX);
      test_all_subarrays(a);
    }
  }
  cout << "Hello World\n";
}
