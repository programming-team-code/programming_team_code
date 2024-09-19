#define PROBLEM                                         \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/3/" \
  "DSL/"                                                \
  "all/DSL_3_D"
#include "../template.hpp"
#include "../../../library/data_structures/deque_op/queue_only.hpp"
int mn(int x, int y) { return min(x, y); }
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, l;
  cin >> n >> l;
  vector<int> arr(n);
  for (int i = 0; i < n; i++) cin >> arr[i];
  vector<int> init(begin(arr), begin(arr) + l);
  deq dq(init, mn);
  cout << dq.query();
  for (int i = l; i < n; i++) {
    dq.push_back(arr[i]);
    dq.pop_front();
    cout << " " << dq.query();
  }
  cout << '\n';
  return 0;
}
