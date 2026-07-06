#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_3_D"
#include "../template.hpp"
#include "../../../library/data_structures_[l,r)/uncommon/deque_op.hpp"
int mn(int x, int y) { return min(x, y); }
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, l;
  cin >> n >> l;
  vi arr(n);
  rep(i, 0, n) cin >> arr[i];
  vi init(begin(arr), begin(arr) + l);
  deq dq(init, mn);
  cout << dq.query();
  rep(i, l, n) {
    dq.push_back(arr[i]);
    dq.pop_front();
    cout << " " << dq.query();
  }
  cout << '\n';
  return 0;
}
