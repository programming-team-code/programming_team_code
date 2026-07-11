#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_3_D"
// since _GLIBCXX_DEBUG causes std::map insert/erase
// operations to be O(n)
#undef _GLIBCXX_DEBUG
#include "../template.hpp"
#include "../../../library/data_structures_[l,r)/uncommon/priority_queue_of_updates.hpp"
struct stack_with_get_max {
  vector<pii> st;
  void join(int val) {
    st.emplace_back(val,
      empty(st) ? val : min(val, st.back().second));
  }
  void undo() { st.pop_back(); }
  int get_max() const { return st.back().second; }
};
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, l;
  cin >> n >> l;
  vi arr(n);
  rep(i, 0, n) cin >> arr[i];
  stack_with_get_max stm;
  pq_updates<stack_with_get_max, int> pq(stm);
  int pri = (n - l) / 2;
  rep(i, 0, l) pq.push_update(arr[i], pri--);
  cout << pq.ds.get_max();
  rep(i, l, n) {
    pq.push_update(arr[i], pri--);
    pq.pop_update();
    cout << " " << pq.ds.get_max();
  }
  cout << '\n';
  return 0;
}
