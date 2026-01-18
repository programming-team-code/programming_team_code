#define PROBLEM "https://judge.yosupo.jp/problem/deque"
#include "../template.hpp"
#include "../../../library/data_structures_[l,r)/uncommon/deque_op.hpp"
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
      int x;
      cin >> x;
      dq.push_front(x);
    } else if (type == 1) {
      int x;
      cin >> x;
      dq.push_back(x);
    } else if (type == 2) {
      dq.pop_front();
    } else if (type == 3) {
      dq.pop_back();
    } else {
      int i;
      cin >> i;
      cout << dq[i] << '\n';
    }
  }
  return 0;
}
