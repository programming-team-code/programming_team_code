#define PROBLEM \
  "https://judge.yosupo.jp/problem/queue_operate_all_composite"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"
#include "../../../library/data_structures_[l,r]/disjoint_rmq.hpp"
#include "../../../library/data_structures_[l,r]/seg_tree.hpp"
const int mod = 998'244'353;
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int q;
  cin >> q;
  vector<array<int, 3>> queries(q);
  vector<array<int, 2>> init;
  for (int i = 0; i < q; i++) {
    int type;
    cin >> type;
    if (type == 0) {
      int a, b;
      cin >> a >> b;
      queries[i] = {type, a, b};
      init.push_back({a, b});
    } else if (type == 1) {
      queries[i] = {type, -1, -1};
    } else {
      int x;
      cin >> x;
      queries[i] = {type, x, -1};
    }
  }
  auto f = [&](const array<int, 2>& l,
             const array<int, 2>& r) -> array<int, 2> {
    return {int(1LL * l[0] * r[0] % mod),
      int((1LL * r[0] * l[1] + r[1]) % mod)};
  };
  tree st(init, f);
  disjoint_rmq rmq(init, f);
  int l = 0, r = 0; //[l,r)
  for (int i = 0; i < q; i++) {
    int type = queries[i][0];
    if (type == 0) {
      r++;
    } else if (type == 1) {
      l++;
    } else {
      int x = queries[i][1];
      assert(l <= r);
      if (l == r) cout << x << '\n';
      else {
        int which = rnd(0, 2);
        st.max_right(l, r - 1,
          [&](int m, const array<int, 2>& val) -> bool {
            assert(l <= m && m <= r - 1);
            assert(val == rmq.query(l, m));
            if (which == 0) return 0;
            else if (which == 1) return 1;
            else return rnd(0, 1);
          });
        st.min_left(l, r - 1,
          [&](int m, const array<int, 2>& val) -> bool {
            assert(l <= m && m <= r - 1);
            assert(val == rmq.query(m, r - 1));
            if (which == 0) return 0;
            else if (which == 1) return 1;
            else return rnd(0, 1);
          });
        array<int, 2> line = rmq.query(l, r - 1);
        cout << (1LL * line[0] * x + line[1]) % mod
             << '\n';
      }
    }
  }
  return 0;
}
