#define PROBLEM \
  "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"
#include "../../../library/data_structures_[l,r)/bit_uncommon/kd_bit.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  for (int num_tests = 0; num_tests < 100; num_tests++) {
    int n = rnd(1, 100);
    int m = rnd(1, 100);
    KD_BIT<2> bit(n, m);
    vector<vector<ll>> a(n, vector<ll>(m, 0));
    for (int events = 0; events < 100; events++) {
      if (events % 2 == 0) {
        int i = rnd(0, n - 1);
        int j = rnd(0, m - 1);
        ll upd = rnd(INT_MIN, INT_MAX);
        a[i][j] += upd;
        bit.update(i, j, upd);
      } else {
        int i1 = rnd(0, n);
        int j1 = rnd(0, m);
        int i2 = rnd(0, n);
        int j2 = rnd(0, m);
        if (i1 > i2) swap(i1, i2);
        if (j1 > j2) swap(j1, j2);
        ll naive = 0;
        for (int i = i1; i < i2; i++)
          for (int j = j1; j < j2; j++) naive += a[i][j];
        assert(naive == bit.query(i1, i2, j1, j2));
      }
    }
  }
  cout << "Hello World\n";
  return 0;
}
