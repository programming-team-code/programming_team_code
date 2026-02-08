#define PROBLEM \
  "https://judge.yosupo.jp/problem/predecessor_problem"
#include "../template.hpp"
#include "../../../library/data_structures_[l,r]/seg_tree.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  string s;
  cin >> s;
  vector<int> init(n);
  for (int i = 0; i < n; i++) init[i] = s[i] - '0';
  tree st(init, plus<int>{});
  while (q--) {
    int type, k;
    cin >> type >> k;
    if (type == 0) {
      if (st.query(k, k) == 0) st.update(k, 1);
    } else if (type == 1) {
      if (st.query(k, k) == 1) st.update(k, 0);
    } else if (type == 2) {
      cout << st.query(k, k) << '\n';
    } else if (type == 3) {
      // returns first element in [k,n-1] such that sum > 0
      int idx = st.walk(k, n - 1,
        [&](int sum) { return sum == 0; });
      if (idx == n) idx = -1;
      cout << idx << '\n';
    } else {
      assert(type == 4);
      int total = st.query(0, k);
      if (total == 0) {
        cout << -1 << '\n';
      } else {
        int pref_sum = 0;
        cout << st.walk(0, k, [&](int sum) {
          if (pref_sum + sum < total) {
            pref_sum += sum;
            return 1;
          }
          return 0;
        }) << '\n';
      }
    }
  }
  return 0;
}
