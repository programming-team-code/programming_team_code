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
  vi init(n);
  rep(i, 0, n) init[i] = s[i] - '0';
  tree st(init, ranges::max);
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
      // index of first element in [k,n-1] such that mx > 0
      int idx = st.max_right(k, n - 1,
        [&](int, int mx) { return mx == 0; });
      cout << (idx == n ? -1 : idx) << '\n';
    } else {
      assert(type == 4);
      // index of last element in [0,k] such that mx > 0
      cout << st.min_left(0, k, [&](int, int mx) {
        return mx == 0;
      }) << '\n';
    }
  }
  return 0;
}
