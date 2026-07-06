#define PROBLEM \
  "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"
#include "../../../library/data_structures_[l,r)/uncommon/hilbert_mos.hpp"
const vi di = {1, -1, 0, 0};
const vi dj = {0, 0, 1, -1};
void test(int i, int j) {
  ll res = hilbert(i, j);
  int cnt_prev = 0;
  int cnt_next = 0;
  rep(k, 0, 4) {
    int to_i = i + di[k];
    int to_j = j + dj[k];
    if (to_i >= 0 && to_j >= 0) {
      cnt_prev += (res - 1 == hilbert(to_i, to_j));
      cnt_next += (res + 1 == hilbert(to_i, to_j));
    }
  }
  if (i == 0 && j == 0) assert(res == 0);
  else assert(cnt_prev == 1);
  assert(cnt_next == 1);
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  rep(i, 0, 3000) rep(j, 0, 3000) test(i, j);
  for (int iter = 50000; iter--;) {
    int i = rnd(0, 1'000'000'000);
    int j = rnd(0, 1'000'000'000);
    test(i, j);
  }
  cout << "Hello World\n";
}
