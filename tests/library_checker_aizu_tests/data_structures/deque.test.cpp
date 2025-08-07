#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/lesson/8/ITP2/all/ITP2_1_B"
#include "../template.hpp"
#include "../../../library/data_structures/uncommon/deque_op.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int q;
  cin >> q;
  deq dq(vector<int>(),
    [](int x, int y) -> int { return min(x, y); });
  while (q--) {
    int type;
    cin >> type;
    if (type == 0) {
      int d, x;
      cin >> d >> x;
      if (d == 0) dq.push_front(x);
      else {
        assert(d == 1);
        dq.push_back(x);
      }
    } else if (type == 1) {
      int p;
      cin >> p;
      cout << dq[p] << '\n';
    } else {
      assert(type == 2);
      int d;
      cin >> d;
      if (d == 0) dq.pop_front();
      else {
        assert(d == 1);
        dq.pop_back();
      }
    }
  }
  return 0;
}
