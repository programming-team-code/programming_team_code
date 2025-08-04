#define PROBLEM \
  "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"
#include "../../../library/data_structures/rmq.hpp"
#include "../../../library/data_structures/uncommon/disjoint_rmq.hpp"
#include "../../../library/data_structures/uncommon/linear_rmq.hpp"
void test_all_subarrays(const vector<int>& a) {
  auto n = sz(a);
  RMQ rmq(a, [](auto x, auto y) { return min(x, y); });
  disjoint_rmq dis_rmq(a,
    [](auto x, auto y) { return min(x, y); });
  linear_rmq lin_rmq(a, less());
  for (int l = 0; l < n; l++) {
    for (int r = l + 1; r <= n; r++) {
      int idx_min = lin_rmq.idx(l, r - 1);
      assert(l <= idx_min && idx_min < r);
      assert(a[idx_min] == rmq.query(l, r));
      assert(a[idx_min] == dis_rmq.query(l, r));
    }
  }
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  for (int n = 1; n <= 8; n++) {
    vector<int> perm(n);
    iota(begin(perm), end(perm), 0);
    do {
      test_all_subarrays(perm);
    } while (next_permutation(begin(perm), end(perm)));
  }
  for (int n = 1; n <= 100; n++) {
    for (int times = 0; times < 40; times++) {
      vector<int> a(n);
      for (int i = 0; i < n; i++)
        a[i] = rnd<int>(INT_MIN, INT_MAX);
      test_all_subarrays(a);
    }
  }
  cout << "Hello World\n";
}
